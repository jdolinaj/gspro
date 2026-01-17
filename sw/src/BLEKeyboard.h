#include <string>
#include "Print.h"

#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <NimBLEUtils.h>
#include <NimBLEHIDDevice.h>


class BleKeyboard :public NimBLEServerCallbacks
{

private:
    NimBLEHIDDevice *hid;
    NimBLECharacteristic *input;
    NimBLEServer *pServer;
    NimBLEAdvertising *pAdvertising;
    std::string deviceName;
    uint8_t batteryLevel;

    bool connected = false;

protected:
  virtual void onStarted(NimBLEServer *pServer) { };
  virtual void onConnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo) override;
  virtual void onDisconnect(NimBLEServer* pServer, NimBLEConnInfo& connInfo, int reason) override;

public:
    BleKeyboard(const std::string& deviceName, uint8_t batteryLevel = 100);
    void begin(void);
    void end(void);

    bool isConnected(void) { return this->connected;}

    void sendKey(uint8_t key, uint8_t modifier = 0);
    void sendCharacter(char ch, uint8_t modifier = 0);
    void sendString(std::string str);
};
