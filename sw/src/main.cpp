#include <esp_log.h>
#include <Wire.h> // Include the Wire library

#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <NimBLEUtils.h>
#include <NimBLEHIDDevice.h>

#include "BLEKeyboard.h"
#include "hid.h"
#include "MCP23017.h"

static const char *TAG = "GSProKB";
#define SDA_PIN 21 // Example SDA pin (check your specific Nano ESP32-C6 board)
#define SCL_PIN 22 // Example SCL pin (check your specific Nano ESP32-C6 board)

// BleKeyboard bleKeyboard("ESP32-KB");

Mobysky_MCP23X17 mcp(SDA_PIN, SCL_PIN, MCP_ADDR);

const int buttonPin = 9;
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // milliseconds

bool portON = false;

// Matrix Config
const int NUM_ROWS = 2;
const int NUM_COLS = 2;

// Keymap (Adjust to match your physical layout)
char keymap[NUM_ROWS][NUM_COLS] = {
  {'1', '2'},
  {'A', 'B'},
};

void i2c_setup()
{
  mcp.begin();
  ESP_LOGD(TAG, "I2C Scanner Started");

  // 1. Configure ROWS (port A) 
  // Set all Port A pins to INPUT (1) and enable pull-ups
  mcp.writeRegister(IODIRA, 0xFF);
  mcp.writeRegister(GPPUA, 0xFF);

  // 2. Configure Port B (COLS)
  // Initially set all Port B pins to INPUT (1) - High Impedance/Floating
  // We only turn them to Output Low one by one.
  mcp.writeRegister(IODIRB, 0xFF); 
  // Disable Pull-ups on Port B (we don't need them for driving low)
  mcp.writeRegister(GPPUB, 0x00);

  // Set Port B Output Latch to LOW (0)
  // Even though they are inputs now, if we switch one to Output, 
  // it will instantly go LOW because of this latch.
  mcp.writeRegister(GPIOB, 0x00);

  ESP_LOGD(TAG,"Keyboard Ready.");
  
};

void i2c_loop() {
// Scan the Matrix
  for (int col = 0; col < NUM_COLS; col++) {
    
    // --- ACTIVATE COLUMN ---
    // To activate a column, we set its specific bit in IODIRB to 0 (Output).
    // Because GPIOB is set to 0x00, this pin will sink to Ground.
    // All other pins remain 1 (Input), so they float.
    
    uint8_t currentDir = 0xFF; // Start with all inputs
    bitClear(currentDir, col); // Set ONLY current col bit to 0 (Output)
    mcp.writeRegister(IODIRB, currentDir);

    // --- READ ROWS ---
    // Read the status of Port A (Rows)
    uint8_t rowState = mcp.readRegister(GPIOA);

    // --- PROCESS ROWS ---
    for (int row = 0; row < NUM_ROWS; row++) {
      // Check if the specific row bit is LOW (0)
      // (Low means pressed because of Pull-up logic)
      if (bitRead(rowState, row) == 0) {
        
        Serial.print("Key Pressed: ");
        Serial.print(keymap[row][col]);
        Serial.print(" (Row: ");
        Serial.print(row);
        Serial.print(", Col: ");
        Serial.print(col);
        Serial.println(")");
        
        // Simple Debounce: Wait a tiny bit so we don't spam Serial
        delay(10); 
      }
    }

    // --- DEACTIVATE COLUMN ---
    // Set everything back to Input (High Z) before moving to next col
    mcp.writeRegister(IODIRB, 0xFF);
  }
  
  // Slow down the main loop slightly
  delay(10);

}

void button_loop() {
    bool buttonState = digitalRead(buttonPin);
  if (buttonState == LOW && lastButtonState == HIGH)
  {
    ESP_LOGD(TAG, ">>> Button pressed!");
    //togle port value
    if (portON)
    {
      //set all pins on port A low
      mcp.writeRegister(0x12, 0x00);
      portON = false;
    } else {
      //set all pins on port A high
      mcp.writeRegister(0x12, 0xFF);
      portON = true;
    }
  }
  lastButtonState = buttonState;
}

void setup()
{
  Serial.begin(115200); // Start serial communication
  ESP_LOGD(TAG, "=== ESP32 BLE Keyboard (NimBLE) ===");

  // bleKeyboard.begin();
  pinMode(buttonPin, INPUT_PULLUP);

  i2c_setup();
}

void loop()
{

  i2c_loop();



  /*
  if (bleKeyboard.isConnected())
  {
    bool buttonState = digitalRead(buttonPin);

    //todo: implement a debounce
    if (buttonState == LOW && lastButtonState == HIGH)
    {
      ESP_LOGD(TAG,">>> Button pressed!");
      bleKeyboard.sendString("Hello, World");
      bleKeyboard.sendKey(0x28); // Enter key

      //bleKeyboard.sendCharacter('v', LEFT_GUI);
      //bleKeyboard.sendString("Hello GS Pro");
      //bleKeyboard.sendKey(KEY_ENTER); // Enter key

      //bleKeyboard.sendCharacter('m', KEY_LEFT_CTRL);
    }

    lastButtonState = buttonState;
  }
  */

  // todo: implement with non blocking delay
  delay(20);
}
