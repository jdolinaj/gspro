/*!
 * @file MCP23X17.h
 */

#ifndef _MCP23X17_H_
#define _MCP23X17_H_

#include <Arduino.h>

#define SDA_PIN 21
#define SCL_PIN 22

#define MCP_ADDR 0x20

#define IODIRA 0x00 // I/O Direction Port A
#define IODIRB 0x01 // I/O Direction Port B
#define GPPUA 0x0C  // Pull-up Resistor Port A
#define GPPUB 0x0D  // Pull-up Resistor Port B
#define GPIOA 0x12  // Input/Output Port A
#define GPIOB 0x13  // Input/Output Port B

/**************************************************************************/
/*!
    @brief  Class for MCP23017 I2C
*/
/**************************************************************************/
class Mobysky_MCP23X17
{
public:
    uint8_t mcp23017_addr;
    uint8_t mcp23017_sda;
    uint8_t mcp23017_scl;

    Mobysky_MCP23X17(u_int8_t i2c_sda, u_int8_t i2c_scl, u_int8_t addr = MCP_ADDR);

    void begin();

    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t value);

};

#endif