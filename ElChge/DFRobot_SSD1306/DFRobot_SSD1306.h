/*!
 * @file DFRobot_SSD1306.h
 * @brief Define the basic structure of class DFRobot_SSD1306
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [lixin](xin.li@dfrobot.com)
 * @version  V1.6.2
 * @date  2019-11-14
 */


#ifndef DFROBOT_SSD1306_H
#define DFROBOT_SSD1306_H

#include <Arduino.h>
#include <Wire.h>
#include <DFRobot_ASCIIfont.h>
#include <DFRobot_CHfont.h>

typedef uint8_t   BYTE;

#define SSD1306_CHARGEPUMP              0x8D
#define SSD1306_COLUMNADDR              0x21
#define SSD1306_COMSCANDEC              0xC8
#define SSD1306_COMSCANINC              0xC0
#define SSD1306_DISPLAYALLON            0xA5
#define SSD1306_DISPLAYALLON_RESUME     0xA4
#define SSD1306_DISPLAYOFF              0xAE
#define SSD1306_DISPLAYON               0xAF
#define SSD1306_EXTERNALVCC             0x01
#define SSD1306_INVERTDISPLAY           0xA7
#define SSD1306_MEMORYMODE              0x20
#define SSD1306_NORMALDISPLAY           0xA6
#define SSD1306_PAGEADDR                0x22
#define SSD1306_SEGREMAP                0xA0
#define SSD1306_SETCOMPINS              0xDA
#define SSD1306_SETCONTRAST             0x81
#define SSD1306_SETDISPLAYCLOCKDIV      0xD5
#define SSD1306_SETDISPLAYOFFSET        0xD3
#define SSD1306_SETHIGHCOLUMN           0x10
#define SSD1306_SETLOWCOLUMN            0x00
#define SSD1306_SETMULTIPLEX            0xA8
#define SSD1306_SETPRECHARGE            0xD9
#define SSD1306_SETSEGMENTREMAP         0xA1
#define SSD1306_SETSTARTLINE            0x40
#define SSD1306_SETVCOMDETECT           0xDB
#define SSD1306_SWITCHCAPVCC            0x02
#define SSD1306_WRITEDATA               0x40
#define SSD1306_WRITECMD                0x80

enum eROTATION
{
    eROTATION_0,
    eROTATION_90,
    eROTATION_180,
    eROTATION_270
};

typedef struct chcode{
    uint16_t  unicode;
    uint32_t  utf8;
    uint16_t  gb2312;
    uint8_t   matrix[32];
}chCode;


/**
  * Base class displayed by SSD1306.
  *
  * Can't be instantiated directly (use DFRobot_SSD1306_I2C)
  */
class DFRobot_SSD1306
{
public:

    /**
     * Constructor
    */
    DFRobot_SSD1306();

    /**
      * @brief Set the slave address and initialize the chip
      *
      * @param address: 8-bit I2C slave address [ addr | 0 ]
      */
    void begin(uint32_t address = 0x3c);

    /**
      * @brief Turn on the display
      */
    void displayON(void);

    /**
      * @brief Display shutdown
      */
    void displayOFF(void);

    /**
      * @brief Fill screen
      *
      * @param color: Set to 0 to show all black, set to 1 to display all white
      */
    void fillScreen(uint32_t color);

    /**
      * @brief Clear a line on the screen
      *
      * @param line: Number of screen lines [1,4]
      *
      * @param color: Set to 0 to show all black, set to 1 to display all white
      */
    void fillInLine(uint32_t line, uint32_t color);
    /**
    * @brief Clear columns x to y in row Z
    *
    * @brief Number of screen lines [1,4]
    *
    * @param color: Set to 0 to show all black, set to 1 to display all white
    */
    // void fillColumns(int16_t line, int16_t column1, int16_t column2, uint32_t color);
    /**
      * @brief Set brush color
      *
      * @param color: Set to 0 to show all black, set to 1 to display all white
      */
    void setBrushColor(uint32_t color);
    /**
      * @brief Get brush color
      *
      * @param color: Get to 0 to show all black, set to 1 to display all white
      */
    uint32_t getBrushColor();

    /**
      * @brief Set cursor coordinates
      *
      * @param x: x coordinate
      *
      * @param y: y coordinate
      */
    void setCursor(int32_t x, int32_t y);

    /**
      * @brief Set the line where the cursor is
      *
      * @param line: Rows
      */
    void setCursorLine(int32_t line);

    /**
      * @brief Set external font dot matrix
      *
      * @param tp: External font dot matrix cache address
      */
    void setChCode(const chCode *tp);

    /**
      * @brief Set the screen rotation angle
      *
      * @param eRotation: angle
      */
    void setRotaion(eROTATION eRotation);

    /**
      * @brief Print a paragraph of text on the screen
      *
      * @param pCh: Memory address of the text
      */
    void print(const char *pCh);

    /**
      * @brief Print a paragraph of text on the screen
      *
      * @param str: Memory address of the text
      */
    void print(String str){print((const char *)str.c_str());}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: uint32_t
      */
    void print(uint32_t i);

    /**
      * @brief Print numbers on the screen
      *
      * @param i: int32_t
      */
    void print(int32_t i);

#if defined(NRF5) || defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
    /**
      * @brief Print numbers on the screen
      *
      * @param i: int
      */
    void print(int i){print((int32_t)i);}
#endif

    /**
      * @brief Print numbers on the screen
      *
      * @param f: double
      *
      * @param precision: Number of reserved bits
      */
    void print(double f, int precision = 10);

    /**
      * @brief Print numbers on the screen
      *
      * @param f: float
      */
    void print(float f){print((double)f);}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: byte
      */
    void print(BYTE i){print((uint32_t)i);}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: uint16_t
      */
    void print(uint16_t i){print((uint32_t)i);}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: int16_t
      */
    void print(int16_t i){print((int32_t)i);}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: uint64_t
      */
    void print(uint64_t i){print((uint32_t)i);}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: int64_t
      */
    void print(int64_t i){print((int32_t)i);}

    /**
      * @brief Print a line of text on the screen
      *
      * @param pCh: Memory address of the text
      */
    void printLine(const char *pCh);

    /**
      * @brief Print a line of text on the screen
      *
      * @param str: Memory address of the text
      */
    void printLine(String str){printLine((const char *)str.c_str());}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: uint32_t
      */
    void printLine(uint32_t i);

    /**
      * @brief Print numbers on the screen
      *
      * @param i: int32_t
      */
    void printLine(int32_t i);

#if defined(NRF5) || defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
    /**
      * @brief Print numbers on the screen
      *
      * @param i: int
      */
    void printLine(int i){printLine((int32_t)i);}
#endif

    /**
      * @brief Print numbers on the screen
      *
      * @param f: double
      *
      * @param precision: Number of reserved bits
      */
    void printLine(double f, int precision = 10);

    /**
      * @brief Print numbers on the screen
      *
      * @param f: float
      */
    void printLine(float f){printLine((double)f);}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: byte
      */
    void printLine(BYTE i){printLine((uint32_t)i);}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: uint16_t
      */
    void printLine(uint16_t i){printLine((uint32_t)i);}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: int16_t
      */
    void printLine(int16_t i){printLine((int32_t)i);}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: uint64_t
      */
    void printLine(uint64_t i){printLine((uint32_t)i);}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: int64_t
      */
    void printLine(int64_t i){printLine((int32_t)i);}

#if defined(ARDUINO_ESP32_DEV) || defined(NRF5) || defined(NRF52833) ||defined(ARDUINO_ARCH_RP2040)
  /**
    * @brief Clear the same line 
    *
    * @param line: Select row
    *
    * @param column1: Starting column
    *
    * @param column2: End column
    *
    * @param color: Set to 0 to clear the specified location
    */
    void fillScreenRange(int32_t line, int32_t column1, int32_t column2, uint32_t color);

    /**
      * @brief Draw any line on the screen
      *
      * @param x0: Starting point x coordinate
      *
      * @param y0: Starting point y coordinate
      *
      * @param x1: End point x coordinate
      *
      * @param y1: End point y coordinate
      */
    void line(int32_t x0, int32_t y0, int32_t x1, int32_t y1);

    /**
      * @brief Draw a rectangle on the screen
      *
      * @param x: Starting point x coordinate
      *
      * @param y: Starting point y coordinate
      *
      * @param width: Rectangular width
      *
      * @param height: Rectangular height
      *
      * @param fill: Setting it to 0 will display a rectangular box on the screen, setting 1 will fill a rectangle on the screen.
      */
    void rect(int32_t x, int32_t y, int32_t width, int32_t height, bool fill = false);

    /**
      * @brief Display a grayscale image on the screen
      *
      * @param x: Starting point x coordinate
      *
      * @param y: Starting point y coordinate
      *
      * @param width: image width
      *
      * @param height: image height
      *
      * @param image: Image cache address
      */
    void drawImage(int32_t x, int32_t y, int32_t width, int32_t height, const uint8_t *image);

    /**
      * @brief Set the line width
      *
      * @param w: Pixel width
      *
      * @note Only for drawing lines and drawing rectangles
      */
    void lineWidth(uint32_t w = 1);

    /**
      * @brief Display a point on the screen
      *
      * @param x: x coordinate
      *
      * @param y: y coordinate
      *
      * @param color: Set to 1 to display black, set to 0 to display white
      */
    void point(int32_t x, int32_t y, uint32_t color = 1);

    /**
      * @brief Draw a round frame on the screen
      *
      * @param x0: Center x coordinate
      *
      * @param y0: Center y coordinate
      *
      * @param r: radius
      */
    void drawCircle(int32_t x0, int32_t y0, int32_t r);

    /**
      * @brief Fill a circle on the screen
      *
      * @param x0: Center x coordinate
      *
      * @param y0: Center y coordinate
      *
      * @param r: radius
      */
    void fillCircle(int32_t x0, int32_t y0, int32_t r);

#if !(defined(NRF5)||defined(NRF52833)||defined(ARDUINO_ARCH_RP2040))
    /**
      * @brief Print numbers on the screen
      *
      * @param i: long unsigned int
      */
    void print(long unsigned int i){print((uint32_t)i);}
    /**
      * @brief Print numbers on the screen
      *
      * @param i: long int
      */
    void print(long int i){print((int32_t)i);}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: long unsigned int
      */
    void printLine(long unsigned int i){printLine((uint32_t)i);}

    /**
      * @brief Print numbers on the screen
      *
      * @param i: long int
      */
    void printLine(long int i){printLine((int32_t)i);}
#endif
#endif

protected:
    int16_t     brushColor;        // Brush color, 0 for black and 1 for white
    int16_t     cursorX, cursorY;  // Cursor position in pixels
    int8_t      cursorLine;          // Cursor position, in units of behavior
    chCode      *tpCode;           // External font dot matrix cache address
#if defined(ARDUINO_ESP32_DEV) || defined(NRF5) || defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
    uint8_t     brushWidth;         // Line width, in pixels
#endif
    uint8_t     address;           // Slave communication address

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
    virtual void setRefreshRange(int address, uint8_t reg, int columnStart, int columnEnd, int rowStart, int rowEnd) = 0;
    /**
      * @brief Write data to the register address in batches
      *
      * @param address: 8-bit I2C slave address [ addr | 0 ]
      *
      * @param reg: The address of the register in the device to write
      *
      * @param data A pointer to a byte buffer containing the data to write
      *
      * @param length The number of bytes to read
      *
      * @return Return the number of data
      */
    virtual int writeBuffer(int address, uint8_t reg, unsigned char *data, int length) = 0;

    /**
      * @brief Write a data to the register address
      *
      * @param address: 8-bit I2C slave address [ addr | 0 ]
      *
      * @param reg: The address of the register in the device to write.
      *
      * @param Data to be written
      *
      * @return Return the number of data
      */
    virtual int writeByte(uint8_t address, uint8_t reg, uint8_t data) = 0;

    /**
      * @brief Direction check
      *
      * @param value: int
      *
      * @return Return 1 in the forward direction and -1 in the reverse direction
      */
    int getDirection(int value);

    /**
      * @brief Ternary expression
      *
      * @param condition: bool
      *
      * @param o1: int
      *
      * @param o2: int
      *
      * @return int
      */
    int ternaryExpression(bool condition, int o1, int o2);

    /**
      * @brief Display a dot matrix text
      *
      * @param x: Starting coordinate x
      *
      * @param y: Starting coordinate y
      *
      * @param width: Text dot matrix width
      *
      * @param height: Text dot matrix height
      *
      * @param pBuf: Text dot matrix cache address
      *
      * @param backColor: Set to true blank area will overwrite the previous pixel, set to false will not overwrite
      */
    void showMatrix(uint8_t x, uint8_t y, int width, int height, const uint8_t *pBuf, bool coverage);

#if defined(ARDUINO_ESP32_DEV) || defined(NRF5) || defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
    uint8_t SSD1306_FrameBuffer[1024]; // Take up 1k of memory and screen cache when memory allows, for more features

    /**
      * @brief Draw a vertical line on the screen (One Pixe)
      *
      * @param x: Starting coordinate x
      *
      * @param y: Starting coordinate y
      *
      * @param height: height
      */
    void VLineOnePixel(int16_t x, int16_t y, int16_t height);

    /**
      * @brief Draw a horizontal line on the screen (One Pixe)
      *
      * @param x: Starting coordinate x
      *
      * @param y: Starting coordinate y
      *
      * @param width: width
      */
    void HLineOnePixel(int16_t x, int16_t y, int16_t width);

    /**
      * @brief Draw a vertical line on the screen
      *
      * @param x: Starting coordinate x
      *
      * @param y: Starting coordinate y
      *
      * @param height: height
      */
    void VLine(int16_t x, int16_t y, int16_t height);

    /**
      * @brief Draw a horizontal line on the screen
      *
      * @param x: Starting coordinate x
      *
      * @param y: Starting coordinate y
      *
      * @param width: width
      */
    void HLine(int16_t x, int16_t y, int16_t width);

    /**
      * @brief Draw a point in the screen cache
      *
      * @param x: Starting coordinate x
      *
      * @param y: Starting coordinate y
      *
      * @param color: color
      */
    void writeBufferPixel(int16_t x, int16_t y, uint16_t color);

    /**
      * @brief Refresh some area data in the cache to the screen display
      *
      * @param x: Starting coordinate x
      *
      * @param y: Starting coordinate y
      *
      * @param width: width
      *
      * @param height: height
      */
    void regionalRefresh(int16_t x, int16_t y, int16_t width, int16_t height);
#endif

private:

};

#endif // DFROBOT_SSD1306_H










