#include "BLEKeyboard.h"
#include "esp_log.h"
#include "hid.h"
#include "timer_util.h"

static const char *TAG = "BleKeyboard";

BleKeyboard::BleKeyboard(const std::string &deviceName, uint8_t batteryLevel) : deviceName(std::string(deviceName).substr(0, 15)), batteryLevel(batteryLevel), hid(nullptr)
{
}

void BleKeyboard::begin(void)
{
    // Initialize NimBLE
    NimBLEDevice::init(deviceName);
    NimBLEDevice::setPower(ESP_PWR_LVL_P9);

    // Security settings
    NimBLEDevice::setSecurityAuth(true, true, true);
    NimBLEDevice::setSecurityIOCap(BLE_HS_IO_NO_INPUT_OUTPUT); // No display, no keyboard

    // Create BLE Server
    pServer = NimBLEDevice::createServer();
    pServer->setCallbacks(this);

    // Create HID Device
    hid = new NimBLEHIDDevice(pServer);
    input = hid->getInputReport(1);

    hid->setManufacturer("Mobysky");
    hid->setPnp(0x02, 0x05ac, 0x820a, 0x0100);
    hid->setHidInfo(0x00, 0x01);

    hid->setReportMap((uint8_t *)reportMap, sizeof(reportMap));
    hid->startServices();

    onStarted(pServer);

    // Start advertising
    pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->setAppearance(HID_KEYBOARD); // keyboard icon
    pAdvertising->addServiceUUID(hid->getHidService()->getUUID());
    pAdvertising->enableScanResponse(false);
    pAdvertising->start();
    hid->setBatteryLevel(batteryLevel);

    ESP_LOGD(TAG, "BLE Keyboard ready. Pair with %s", deviceName.c_str());
}

void BleKeyboard::end(void)
{
    if (hid != nullptr) {
        delete hid;
        hid = nullptr;
    }
    
}

void BleKeyboard::onConnect(NimBLEServer *pServer, NimBLEConnInfo &connInfo)
{
    this->connected = true;

    ESP_LOGD(TAG, "✓ Device connected! #con=%d", pServer->getConnectedCount());

    // Stop advertising when connected
    NimBLEDevice::getAdvertising()->stop();

    // Update connection parameters for better keyboard performance
    pServer->updateConnParams(connInfo.getConnHandle(), 24, 48, 0, 60);
}

void BleKeyboard::onDisconnect(NimBLEServer *pServer, NimBLEConnInfo &connInfo, int reason)
{
    this->connected = false;

    ESP_LOGD(TAG, "✗ Device disconnected (reason: 0x%02x)", reason);

    // Start advertising as we are disconnected and we allow only one connection
    NimBLEDevice::startAdvertising();

    ESP_LOGD(TAG, "Advertising restarted...");
}

void BleKeyboard::sendKey(uint8_t key, uint8_t modifier)
{
    // HID Report: [modifier, reserved, key1, key2, key3, key4, key5, key6]
    uint8_t report[8] = {modifier, 0, key, 0, 0, 0, 0, 0};
    ESP_LOGD(TAG, "Send: 0x%02x modifier: 0x%02x", key, modifier);

    input->setValue(report, 8);
    input->notify();
    delay_ms(5);

    // Release all keys
    uint8_t release[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    input->setValue(release, 8);
    input->notify();
    // delay_ms(2);
}

void BleKeyboard::sendCharacter(char ch, uint8_t modifier)
{
    uint8_t c = (uint8_t)ch;
    if (c < 128)
    {
        uint8_t key = ascii_to_hid[c].key; // Look up the HID code
        uint8_t totalModifier = modifier | ascii_to_hid[c].modifier;

        if (key != 0)
        {
            sendKey(key, totalModifier);
        }
    }
}

void BleKeyboard::sendString(std::string str)
{
    ESP_LOGD(TAG, "Send: %s", str.c_str());

    for (char ch : str)
    {
        uint8_t c = (uint8_t)ch;
        // Bounds check to ensure we only process standard ASCII
        if (c < 128)
        {
            uint8_t key = ascii_to_hid[c].key;
            uint8_t modifier = ascii_to_hid[c].modifier;

            if (key != 0)
            {
                sendKey(key, modifier);
            }
        }
    }
}