// filepath: /home/jan/Projects/esp32/gspro/src/MCP23X17.cpp
#include "MCP23017.h"
#include <Wire.h>
#include <stdint.h>

static const char *TAG = "Mobysky_MCP23017";


Mobysky_MCP23X17::Mobysky_MCP23X17(u_int8_t i2c_sda, u_int8_t i2c_scl, u_int8_t addr) {
    mcp23017_addr = addr;
    mcp23017_sda = i2c_sda;
    mcp23017_scl = i2c_scl;
}

void Mobysky_MCP23X17::begin() {
    ESP_LOGD(TAG, "Mobysky_MCP23X17 wire begin on SDA: %d SCL: %d", mcp23017_sda, mcp23017_scl);
    Wire.begin(mcp23017_sda, mcp23017_scl);

}

void Mobysky_MCP23X17::writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(mcp23017_addr);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

uint8_t Mobysky_MCP23X17::readRegister(uint8_t reg) {
    Wire.beginTransmission(mcp23017_addr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom(mcp23017_addr, 1);
    return Wire.read();
}






/*

uint8_t Mobysky_MCP23X17::readGPIOA() {
    return readRegister(MCP23017_BASE_ADDR, REG_GPIOA);
}

void Mobysky_MCP23X17::writeGPIOA(uint8_t value) {
    writeRegister(MCP23017_BASE_ADDR, REG_OLATA, value);
}

uint8_t Mobysky_MCP23X17::readGPIOB() {
    return readRegister(MCP23017_BASE_ADDR, REG_GPIOB);
}

void Mobysky_MCP23X17::writeGPIOB(uint8_t value) {
    writeRegister(MCP23017_BASE_ADDR, REG_OLATB, value);
}

uint16_t Mobysky_MCP23X17::readGPIOAB() {
    // Read GPIOA then GPIOB and combine: A = low byte, B = high byte
    uint8_t a = readGPIOA();
    uint8_t b = readGPIOB();
    return (uint16_t)a | (uint16_t(b) << 8);
}

void Mobysky_MCP23X17::writeGPIOAB(uint16_t value) {
    uint8_t low = value & 0xFF;
    uint8_t high = (value >> 8) & 0xFF;
    // write both registers in one transaction starting at OLATA (0x14) or GPIOA (0x12)
    Wire.beginTransmission(MCP23017_BASE_ADDR);
    Wire.write(REG_OLATA);
    Wire.write(low);
    Wire.write(high);
    Wire.endTransmission();
}

void Mobysky_MCP23X17::enableAddrPins() {
    // Set IOCON.HAEN bit (bit 3) to enable hardware addressing if supported
    uint8_t iocon = readRegister(MCP23017_BASE_ADDR, REG_IOCON);
    iocon |= (1 << 3); // HAEN
    writeRegister(MCP23017_BASE_ADDR, REG_IOCON, iocon);
}

    
    
*/