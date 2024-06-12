/*!
 * @file DFRobot_SSD1306_I2C.h
 * @brief Define the basic structure of class DFRobot_SSD1306_I2C
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [lixin](xin.li@dfrobot.com)
 * @version  V1.6.2
 * @date  2019-11-14
 */


#ifndef DFROBOT_SSD1306_I2C_H
#define DFROBOT_SSD1306_I2C_H

#include "DFRobot_SSD1306.h"
#include "Wire.h"

#define SSD1306_I2CBEGIN()        Wire.setClock(400000);



/**
  * Class definition for DFRobot_SSD1306_I2C.
  *
  * Represents an instance of DFRobot_SSD1306 that accepts the I2C version of SSD1306
  */
class DFRobot_SSD1306_I2C : public DFRobot_SSD1306
{
public:

    /**
     * Constructor
     *
     * @brief Create an instance of DFRobot_SSD1306_I2C
     */
    DFRobot_SSD1306_I2C();

private:

    /**
      * @brief Set screen cache refresh range
      *
      * @param address: 8-bit I2C slave address [ addr | 0 ]
      *
      * @param reg: The address of the register in the device to write
      *
      * @param columnStart: Column start position
      *
      * @param columnEnd: End of column
      *
      * @param rowStart: Line start position
      *
      * @param rowEnd: End of line
      */
    void setRefreshRange(int address, uint8_t reg, int columnStart, int columnEnd, int rowStart, int rowEnd);

    /**
      * @brief Write data to the register address in batches
      *
      * @param address: 8-bit I2C slave address [ addr | 0 ]
      *
      * @param reg: The address of the register in the device to write
      *
      * @param data: A pointer to a byte buffer containing the data to write
      *
      * @param length: The number of bytes to read
      *
      * @return Return the number of data
      */
    int writeBuffer(int address, uint8_t reg, unsigned char *data, int length);

    /**
      * @brief Write a data to the register address
      *
      * @param address: 8-bit I2C slave address [ addr | 0 ]
      *
      * @param reg: The address of the register in the device to write.
      *
      * @param Data: to be written
      *
      * @return Return the number of data
      */
    int writeByte(uint8_t address, uint8_t reg, uint8_t data);
};

#endif // DFROBOT_SSD1306_I2C_H