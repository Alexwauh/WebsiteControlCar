/*!
 * @file DFRobot_SSD1306.cpp
 * @brief Define the basic structure of class DFRobot_SSD1306
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [lixin](xin.li@dfrobot.com)
 * @version  V1.6.2
 * @date  2019-11-14
 */


#include "DFRobot_SSD1306.h"
#if defined(ARDUINO_ESP32_DEV)
#include "MPython_Font.h"
#endif


/**
 * Constructor
*/
DFRobot_SSD1306::DFRobot_SSD1306() : 
    brushColor(1),
    cursorX(0),
    cursorY(0),
    cursorLine(1),
    tpCode(NULL),
#if defined(ARDUINO_ESP32_DEV) || defined(NRF5)||defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
    brushWidth(1),
#endif
    address(0x3c)
{
    // do nothing
}

/**
  * @brief Set the slave address and initialize the chip
  *
  * @param address: 8-bit I2C slave address [ addr | 0 ]
  */
void DFRobot_SSD1306::begin(uint32_t address)
{
    this->address = address;
    Wire.begin();
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_DISPLAYOFF);
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_SETDISPLAYCLOCKDIV);
    writeByte(this->address, SSD1306_WRITECMD, 0xF0); // Increase speed of the display max ~96Hz
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_SETMULTIPLEX);
    writeByte(this->address, SSD1306_WRITECMD, 0x3F);
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_SETDISPLAYOFFSET);
    writeByte(this->address, SSD1306_WRITECMD, 0x00);
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_SETSTARTLINE);
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_CHARGEPUMP);
    writeByte(this->address, SSD1306_WRITECMD, 0x14);
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_MEMORYMODE);
    writeByte(this->address, SSD1306_WRITECMD, 0x00);
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_SEGREMAP);
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_COMSCANINC);
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_SETCOMPINS);
    writeByte(this->address, SSD1306_WRITECMD, 0x12);
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_SETCONTRAST);
    writeByte(this->address, SSD1306_WRITECMD, 0xCF);
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_SETPRECHARGE);
    writeByte(this->address, SSD1306_WRITECMD, 0xF1);
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_DISPLAYALLON_RESUME);
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_NORMALDISPLAY);
    writeByte(this->address, SSD1306_WRITECMD, 0x2e); // stop scroll
    writeByte(this->address, SSD1306_WRITECMD, SSD1306_DISPLAYON);
    setRotaion(eROTATION_180);
    fillScreen(0);
    setBrushColor(1);
#if defined(ARDUINO_ESP32_DEV)
    mFont.init();
#endif
}

/**
  * @brief Turn on the display
  */
void DFRobot_SSD1306::displayON()
{
    writeByte(this->address, SSD1306_WRITECMD, 0xaf);
}

/**
  * @brief Display shutdown
  */
void DFRobot_SSD1306::displayOFF(void)
{
    writeByte(this->address, SSD1306_WRITECMD, 0xae);
}

/**
  * @brief Fill screen
  *
  * @param color: Set to 0 to show all black, set to 1 to display all white
  */
void DFRobot_SSD1306::fillScreen(uint32_t color)
{
#if defined(ARDUINO_ESP32_DEV) || defined(NRF5)||defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
    if(color) {
        memset(SSD1306_FrameBuffer, 0xff, 1024);
        } else {
        memset(SSD1306_FrameBuffer, 0, 1024);
    }
    regionalRefresh(0, 0, 128, 64);
#else
    uint8_t    i = 0, j = 0;
    uint8_t    buf[16];
    if(color) {
        memset(buf, 0xff, 16);
    } else{
        memset(buf, 0, 16);
    }
    setRefreshRange(this->address, SSD1306_WRITECMD, 0, 127, 0, 7);
    for(i = 0; i < 128 * 64 / 8 / 16; i ++) {
        writeBuffer(this->address, SSD1306_WRITEDATA, buf, 16);
    }
#endif
}

/**
  * @brief Clear a line on the screen
  *
  * @param line: Number of screen lines [1,4]
  *
  * @param color: Set to 0 to show all black, set to 1 to display all white
  */
void DFRobot_SSD1306::fillInLine(uint32_t line, uint32_t color)
{
    line = constrain(line, 1, 4);
#if defined(ARDUINO_ESP32_DEV) || defined(NRF5)||defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
    if(color) {
        memset(SSD1306_FrameBuffer+((line-1)*256), 0xff, 256);
        } else {
        memset(SSD1306_FrameBuffer+((line-1)*256), 0, 256);
    }
    regionalRefresh(0, ((line-1)*16), 128, 16);
#else
    uint8_t    i = 0, j = 0;
    uint8_t    buf[16];
    if(color) {
        memset(buf, 0xff, 16);
    } else{
        memset(buf, 0, 16);
    }
    setRefreshRange(this->address, SSD1306_WRITECMD, 0, 127, (line-1)*2, line*2);
    for(i = 0; i < 128 * 16 / 8 / 16; i ++) {
        writeBuffer(this->address, SSD1306_WRITEDATA, buf, 16);
    }
#endif
}

/**
  * @brief Set brush color
  *
  * @param color: Set to 0 to show all black, set to 1 to display all white
  */
void DFRobot_SSD1306::setBrushColor(uint32_t color)
{
    brushColor = color;
}

/**
  * @brief Get brush color
  *
  * @param color: Get to 0 to show all black, set to 1 to display all white
  */
uint32_t DFRobot_SSD1306::getBrushColor()
{
    return brushColor;
}

/**
  * @brief Set cursor coordinates
  *
  * @param x: x coordinate
  *
  * @param y: y coordinate
  */
void DFRobot_SSD1306::setCursor(int32_t x, int32_t y)
{
#if defined(ARDUINO_ESP32_DEV) || defined(NRF5)||defined(NRF52833)
    if(x<0) x=0;
    if(x>127) x=127;
    if(y<0) y=0;
    if(y>63) y=63;
    cursorX = x;
    cursorY = y;
#else
    if(x > 127) {
        cursorX = 127;
    } else {
        cursorX = x;
    }
    y = 16 * y;
    if(y>=0 && y<16)
        cursorY = 0;
    else if(y>=16 && y<32)
        cursorY = 16;
    else if(y>=32 && y<48)
        cursorY = 32;
    else if(y>=48 && y<64)
        cursorY = 48;
    else if(y>=64)
        cursorY = 48;
    else
        cursorY = 0;
#endif
}

/**
  * @brief Set the line where the cursor is
  *
  * @param line: Rows
  */
void DFRobot_SSD1306::setCursorLine(int32_t line)
{
    line = constrain(line, 1, 4);
    cursorLine = line%4;
    if(cursorLine == 0)
        cursorLine = 4;
}

/**
  * @brief Set external font dot matrix
  *
  * @param tp: External font dot matrix cache address
  */
void DFRobot_SSD1306::setChCode(const chCode *tp)
{
    tpCode = (chCode *)tp;
}

/**
  * @brief Set the screen rotation angle
  *
  * @param eRotation: angle
  */
void DFRobot_SSD1306::setRotaion(eROTATION eRotation)
{
#if defined(ARDUINO_ESP32_DEV) || defined(NRF5)||defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
    uint8_t buf[16];
	memset(buf, 0, 16);
    for(uint8_t i=0; i < 8; i++)
    {
        setRefreshRange(this->address, SSD1306_WRITECMD, 0, 127, i, i);
        uint8_t j;
        for(j = 0; j < 8; j++)
        {
            writeBuffer(this->address, SSD1306_WRITEDATA, buf, 16);
        }
    }
#endif
    switch(eRotation) {
        case eROTATION_0:
            writeByte(this->address, SSD1306_WRITECMD, 0xa0);
            writeByte(this->address, SSD1306_WRITECMD, 0xc0); 
            break;
        case eROTATION_180:
            writeByte(this->address, SSD1306_WRITECMD, 0xa1);
            writeByte(this->address, SSD1306_WRITECMD, 0xc8);
            break;
        default: 
            writeByte(this->address, SSD1306_WRITECMD, 0xa1);
            writeByte(this->address, SSD1306_WRITECMD, 0xc8);
            break;
    }
#if defined(ARDUINO_ESP32_DEV) || defined(NRF5)||defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
    regionalRefresh(0, 0, 128, 64);
#else
    fillScreen(0);
#endif
}

/**
  * @brief Direction check
  *
  * @param value: int
  *
  * @return Return 1 in the forward direction and -1 in the reverse direction
  */
int DFRobot_SSD1306::getDirection(int value)
{
    if (value >= 0)
        return 1;
    return -1;
}

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
int DFRobot_SSD1306::ternaryExpression(bool condition, int o1, int o2)
{
    if(condition)
        return o1;
    return o2;
}

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
  * @param coverage: Set to true blank area will overwrite the previous pixel, set to false will not overwrite
  */
void DFRobot_SSD1306::showMatrix(uint8_t x, uint8_t y, int width, int height, const uint8_t *pBuf, bool coverage)
{
    if(!pBuf) return;
    if(x>127 || y>63) return;
    if(height%8 !=0) return;

    int i,j,k;
    uint8_t _x;
    uint8_t _y;
    int widthSize = width/8;
    int heightSize = height/8;

#if defined(ARDUINO_ESP32_DEV) || defined(NRF5)||defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
    _x = x;
    _y = y;
#else
    _x = 0;
    _y = 0;
    int writeWidth = width;
    int matrixSize = width * height / 8;
    uint8_t matrixBuffer[matrixSize];
    memset(matrixBuffer, 0, matrixSize);
    int16_t bufferAddr = 0;
#endif

    for(i=0; i<height; i++)
    {
        if(_y > 63) break;
        for(j=0; j<widthSize; j++)
        {
            uint8_t data = *pBuf;
            for(k=0; k<8; k++)
            {
                if(_x > 127) break;
#if defined(ARDUINO_ESP32_DEV) || defined(NRF5)||defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
                if(data & 0x80) {
                    writeBufferPixel(_x, _y, brushColor == 1 ? 1 : 0);
                } else {
                    if(coverage) {
                        writeBufferPixel(_x, _y, brushColor == 1 ? 0 : 1);
                    }
                }
#else
                bufferAddr = _x + _y / 8 * width;
                if(data & 0x80) {
                    if(brushColor == 1) {
                        matrixBuffer[bufferAddr] |= (0x01 << (_y % 8));
                    }else{
                        matrixBuffer[bufferAddr] &= ~ (0x01 << (_y % 8));
                    }
                } else {
                    if(coverage) {
                        if(brushColor == 1) {
                            matrixBuffer[bufferAddr] &= ~ (0x01 << (_y % 8));
                        }else{
                            matrixBuffer[bufferAddr] |= (0x01 << (_y % 8));
                        }
                    }
                }
#endif
                data <<= 1;
                _x++;
            }
            pBuf++;
        }
#if defined(ARDUINO_ESP32_DEV) || defined(NRF5)||defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
        _x = x;
#else
        _x = 0;
#endif
        _y++;
    }

#if defined(ARDUINO_ESP32_DEV) || defined(NRF5)||defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
    regionalRefresh(x,y,width,height);
#else
    _x = x, _y = y;
    for(i=0; i<heightSize; i++)
    {
        setRefreshRange(this->address, SSD1306_WRITECMD, _x, _x + width -1, (_y+i*8) / 8, (_y+i*8) / 8);
        writeBuffer(this->address, SSD1306_WRITEDATA, matrixBuffer + i*width,writeWidth);
    }
#endif
}

/**
  * @brief Print a paragraph of text on the screen
  *
  * @param pCh: Memory address of the text
  */
void DFRobot_SSD1306::print(const char *pCh)
{
#if defined(ARDUINO_ESP32_DEV)
    while(*pCh != '\0' && pCh != NULL)
    {
        //utf-8 code
        if((*pCh & 0xf0) == 0xe0 && (*(pCh + 1) & 0xc0) == 0x80 && (*(pCh + 2) & 0xc0) == 0x80 || (*pCh == 0xc2 && *(pCh + 1) == 0xb7)) {
            char utf8[3];
            if(*pCh == 0xc2 && *(pCh + 1) == 0xb7) {
                utf8[0] = 0x00;
                utf8[1] = 0xc2;
                utf8[2] = 0xb7;
            }else{
                utf8[0] = *pCh;
                utf8[1] = *(pCh+1);
                utf8[2] = *(pCh+2);
            }
            mfontOne fontOne = mFont.getCharacterData((const char *)utf8);
            if(cursorX + fontOne.width > 127){
                cursorY += 16;
                cursorX = 0;
            }
            if(cursorY > 64)
                return;
            showMatrix(cursorX,cursorY, fontOne.bytes_per_line * 8, 16, fontOne.data, true);
            cursorX += (fontOne.width+1);
            if(*pCh == 0xc2 && *(pCh + 1) == 0xb7) {
                pCh += 2;
            }else{
                pCh += 3;
            }
        //gb2312
        } else if((*pCh & 0x80) == 0x80) {
            char gb2312[2] = {*(pCh), *(pCh+1)};
            mfontOne fontOne = mFont.getCharacterData((const char *)gb2312);
            if(cursorX + fontOne.width > 127){
                cursorY += 16;
                cursorX = 0;
            }
            if(cursorY > 64)
                return;
            showMatrix(cursorX,cursorY, fontOne.bytes_per_line * 8, 16, fontOne.data, true);
            cursorX += (fontOne.width+1);
            pCh += 2;
        //char code
        } else {
            uint8_t ascii = (uint8_t)*pCh;
            mfontOne fontOne = mFont.getCharacterData((const char *)&ascii);
            if(cursorX + fontOne.width > 127){
                cursorY += 16;
                cursorX = 0;
            }
            if(cursorY > 64)
                return;
            showMatrix(cursorX,cursorY, fontOne.bytes_per_line * 8, 16, fontOne.data, true);
            cursorX += (fontOne.width+1);
            pCh += 1;
        }
    }
#else
    chCode *p = NULL;
    bool findCh;

    while(*pCh != '\0' && pCh != NULL)
    {
        //utf-8 code
        if((*pCh & 0xf0) == 0xe0 && (*(pCh + 1) & 0xc0) == 0x80 && (*(pCh + 2) & 0xc0) == 0x80 || (*pCh == 0xc2 && *(pCh + 1) == 0xb7)) {
            uint32_t utf8;
            if(*pCh == 0xc2 && *(pCh + 1) == 0xb7) {
                utf8 = 0xc2b7;
            }else{
                utf8 = (0x00ff0000 & (uint32_t)*pCh << 16) | (0x0000ff00 & (uint32_t)*(pCh+1) << 8) | (0x000000ff & (uint32_t)*(pCh+2));
            }
            p = tpCode;
            findCh = false;
            if(p){
                while(p->utf8)
                {
                    if(p->utf8 == utf8)
                    {
                        if(cursorX + 16 > 130){
                            cursorY += 16;
                            cursorX = 0;
                        }
                        if(cursorY > 64)
                            return;
                        showMatrix(cursorX,cursorY, 16, 16, p->matrix, true);
                        findCh = true;
                        break;
                    }
                    p++;
                }
            }
            if(!findCh){
                chfont* pt = DFFont.listhead;
                while(pt){
                    p = (chCode *)(DFFont.listhead->code);
                    if(p){
                        while(p->utf8){
                            if(p->utf8 == utf8)
                            {
                                if(cursorX + 16 > 130){
                                    cursorY += 16;
                                    cursorX = 0;
                                }
                                if(cursorY > 64)
                                    return;
                                showMatrix(cursorX,cursorY, 16, 16, p->matrix, true);
                                findCh = true;
                                break;
                            }
                            p++;
                        }
                    }
                    pt = pt->next;
                }
                //DFFont
            }
            cursorX += 16;
            if(*pCh == 0xc2 && *(pCh + 1) == 0xb7) {
                pCh += 2;
            }else{
                pCh += 3;
            }
        //gb2312
        } else if((*pCh & 0x80) == 0x80) {
            uint16_t gb2312 = (0xff00 & (uint16_t)*(pCh) << 8) | (0x00ff & (uint16_t)*(pCh+1));
            p = tpCode;
            findCh = false;
            if(p){
                while(p->gb2312)
                {
                    if(p->gb2312 == gb2312)
                    {
                        if(cursorX + 16 > 130){
                            cursorY += 16;
                            cursorX = 0;
                        }
                        if(cursorY > 64)
                            return;
                        showMatrix(cursorX,cursorY, 16, 16, p->matrix, true);
                        findCh = true;
                        break;
                    }
                    p++;
                }
            }
            if(!findCh){
                chfont* pt = DFFont.listhead;
                while(pt){
                    p = (chCode *)(DFFont.listhead->code);
                    if(p){
                        while(p->gb2312){
                            if(p->gb2312 == gb2312)
                            {
                                if(cursorX + 16 > 130){
                                    cursorY += 16;
                                    cursorX = 0;
                                }
                                if(cursorY > 64)
                                    return;
                                showMatrix(cursorX,cursorY, 16, 16, p->matrix, true);
                                findCh = true;
                                break;
                            }
                            p++;
                        }
                    }
                    pt = pt->next;
                }
                //DFFont
            }
            cursorX += 16;
            pCh += 2;
        //char code
        } else {
            uint8_t ascii = (uint8_t)*pCh -32;
            uint8_t date[16];

            if(cursorX + 8 > 127){
                cursorY += 16;
                cursorX = 0;
            }
            if(cursorY > 64)
                return;
        
            for(int i=0; i<16; i++)
            {
                #ifdef AVR
                date[i] = pgm_read_byte(&ascii_8_16[ascii][i]);
                #else
                date[i] = ascii_8_16[ascii][i];
                #endif
            }
            if(*pCh == 0x20) showMatrix(cursorX,cursorY, 8, 16, date, true);
            else showMatrix(cursorX,cursorY, 8, 16, date, true);
            cursorX += 8;
            pCh += 1;
        }
    }
#endif
}

/**
  * @brief Print numbers on the screen
  *
  * @param i: uint32_t
  */
void DFRobot_SSD1306::print(uint32_t i)
{
    char buffer[34];
    memset(buffer, 0, 34);
    itoa(i, buffer, 10);
    print(buffer);
}

/**
  * @brief Print numbers on the screen
  *
  * @param i: int32_t
  */
void DFRobot_SSD1306::print(int32_t i)
{
    char buffer[34];
    memset(buffer, 0, 34);
    itoa(i, buffer, 10);
    print(buffer);
}

/**
  * @brief Print numbers on the screen
  *
  * @param f: double
  *
  * @param precision: Number of reserved bits
  */
void DFRobot_SSD1306::print(double f, int precision)
{
    String str;
    str = String(f,5);

    char *p = (char *)(str.c_str() + str.length());
    while(*p == '\0'|| *p == '0'){
        *p = '\0';
        p--;
    }
    if(*p == '.')
        *p = '\0';
    if(str == "-0")
        str = "0";
    print(str);
}

/**
  * @brief Print a line of text on the screen
  *
  * @param pCh: Memory address of the text
  */
void DFRobot_SSD1306::printLine(const char *pCh)
{
    int16_t X=0, Y = 16 * (cursorLine-1);
    fillInLine(cursorLine, brushColor == 1 ? 0 : 1);
#if defined(ARDUINO_ESP32_DEV)
    while(*pCh != '\0' && pCh != NULL)
    {
        //utf-8 code
        if((*pCh & 0xf0) == 0xe0 && (*(pCh + 1) & 0xc0) == 0x80 && (*(pCh + 2) & 0xc0) == 0x80 || (*pCh == 0xc2 && *(pCh + 1) == 0xb7)) {
            char utf8[3];
            if(*pCh == 0xc2 && *(pCh + 1) == 0xb7) {
                utf8[0] = 0x00;
                utf8[1] = 0xc2;
                utf8[2] = 0xb7;
            }else{
                utf8[0] = *pCh;
                utf8[1] = *(pCh+1);
                utf8[2] = *(pCh+2);
            }
            mfontOne fontOne = mFont.getCharacterData((const char *)utf8);
            if(X + fontOne.width > 127)
                return;
            showMatrix(X,Y, fontOne.bytes_per_line * 8, 16, fontOne.data, true);

            X += (fontOne.width+1);
            if(*pCh == 0xc2 && *(pCh + 1) == 0xb7) {
                pCh += 2;
            }else{
                pCh += 3;
            }
        //gb2312
        } else if((*pCh & 0x80) == 0x80) {
            char gb2312[2] = {*(pCh), *(pCh+1)};
            mfontOne fontOne = mFont.getCharacterData((const char *)gb2312);
            if(X + fontOne.width > 127)
                return;
            showMatrix(X,Y, fontOne.bytes_per_line * 8, 16, fontOne.data, true);
            X += (fontOne.width+1);
            pCh += 2;
        //char code
        } else {
            uint8_t ascii = (uint8_t)*pCh;
            mfontOne fontOne = mFont.getCharacterData((const char *)&ascii);
            if(X + fontOne.width > 127)
                return;
            showMatrix(X, Y, fontOne.bytes_per_line * 8, 16, fontOne.data, true);
            X += (fontOne.width+1);
            pCh += 1;
        }
    }
#else
    bool findCh;
    chCode *p = NULL;
    while(*pCh != '\0' && pCh != NULL)
    {
        //utf-8 code
        if((*pCh & 0xf0) == 0xe0 && (*(pCh + 1) & 0xc0) == 0x80 && (*(pCh + 2) & 0xc0) == 0x80 || (*pCh == 0xc2 && *(pCh + 1) == 0xb7)) {
            uint32_t utf8;
            if(*pCh == 0xc2 && *(pCh + 1) == 0xb7) {
                utf8 = 0xc2b7;
            }else{
                utf8 = (0x00ff0000 & (uint32_t)*pCh << 16) | (0x0000ff00 & (uint32_t)*(pCh+1) << 8) | (0x000000ff & (uint32_t)*(pCh+2));
            }
            p = tpCode;
            if(p){
                while(p->utf8)
                {
                    if(p->utf8 == utf8)
                    {
                        if(X+16 > 128)
                            return;
                        showMatrix(X,Y, 16, 16, p->matrix, true);
                        findCh = true;
                        break;
                    }
                    p++;
                }
            }
            if(!findCh){
                chfont* pt = DFFont.listhead;
                while(pt){
                    p = (chCode *)(DFFont.listhead->code);
                    if(p){
                        while(p->utf8){
                            if(p->utf8 == utf8)
                            {
                                if(X+16 > 128)
                                    return;
                                showMatrix(X,Y, 16, 16, p->matrix, true);
                                findCh = true;
                                break;
                            }
                            p++;
                        }
                    }
                    pt = pt->next;
                }
                //DFFont
            }
            X += 16;
            if(*pCh == 0xc2 && *(pCh + 1) == 0xb7) {
                pCh += 2;
            }else{
                pCh += 3;
            }
        //gb2312
        } else if((*pCh & 0x80) == 0x80) {
            uint16_t gb2312 = (0xff00 & (uint16_t)*(pCh) << 8) | (0x00ff & (uint16_t)*(pCh+1));
            p = tpCode;
            findCh = false;
            if(p){
                while(p->gb2312)
                {
                    if(p->gb2312 == gb2312)
                    {
                        if(X+16 > 128)
                            return;
                        showMatrix(X,Y, 16, 16, p->matrix, true);

                        break;
                    }
                    p++;
                }
            }
            if(!findCh){
                chfont* pt = DFFont.listhead;
                while(pt){
                    p = (chCode *)(DFFont.listhead->code);
                    if(p){
                        while(p->gb2312){
                            if(p->gb2312 == gb2312)
                            {
                                if(p->gb2312 == gb2312)
                                {
                                    if(X+16 > 128)
                                        return;
                                    showMatrix(X,Y, 16, 16, p->matrix, true);

                                    break;
                                }
                                p++;
                            }
                            p++;
                        }
                    }
                    pt = pt->next;
                }
                //DFFont
            }
            X += 16;
            pCh += 2;
        //char code
        } else {
            uint8_t ascii = (uint8_t)*pCh -32;
            uint8_t date[16];

            if(X+8 > 128)
                return;
        
            for(int i=0; i<16; i++)
            {
                #ifdef AVR
                date[i] = pgm_read_byte(&ascii_8_16[ascii][i]);
                #else
                date[i] = ascii_8_16[ascii][i];
                #endif
            }
            if(*pCh == 0x20) showMatrix(X,Y, 8, 16, date, true);
            else showMatrix(X,Y, 8, 16, date, true);
            X += 8;
            pCh += 1;
        }
    }
#endif
}

/**
  * @brief Print numbers on the screen
  *
  * @param i: uint32_t
  */
void DFRobot_SSD1306::printLine(uint32_t i)
{
    char buffer[34];
    memset(buffer, 0, 34);
    itoa(i, buffer, 10);
    printLine(buffer);
}

/**
  * @brief Print numbers on the screen
  *
  * @param i: int32_t
  */
void DFRobot_SSD1306::printLine(int32_t i)
{
    char buffer[34];
    memset(buffer, 0, 34);
    itoa(i, buffer, 10);
    printLine(buffer);
}

/**
  * @brief Print numbers on the screen
  *
  * @param f: double
  *
  * @param precision: Number of reserved bits
  */
void DFRobot_SSD1306::printLine(double f, int precision)
{
    String str;
    str = String(f,5);
    char *p = (char *)(str.c_str() + str.length());
    while(*p == '\0'|| *p == '0'){
        *p = '\0';
        p--;
    }
    if(*p == '.')
        *p = '\0';
    if(str == "-0")
        str = "0";
    printLine(str);
}

#if defined(ARDUINO_ESP32_DEV) || defined(NRF5)||defined(NRF52833)||defined(ARDUINO_ARCH_RP2040)
/**
  * @brief Display a point on the screen
  *
  * @param x: x coordinate
  *
  * @param y: y coordinate
  *
  * @param color: Set to 1 to display black, set to 0 to display white
  */
void DFRobot_SSD1306::point(int32_t x, int32_t y, uint32_t color)
{
    x = max(min(x, 127), 0);
    y = max(min(y, 63), 0);
    writeBufferPixel(x, y, color);
    regionalRefresh(x, y, 1, 1);
}

/**
  * @brief Draw a round frame on the screen
  *
  * @param x0: Center x coordinate
  *
  * @param y0: Center y coordinate
  *
  * @param r: radius
  */
void DFRobot_SSD1306::drawCircle(int32_t x0, int32_t y0, int32_t r)
{
    r = abs(r);
    int16_t       varX = 0, varY = r;
    int16_t       endY = 0;
    int32_t       var1 = 3 - 2 * r;

    while(varX <= varY) {
        writeBufferPixel(x0 + varX, y0 + varY, 1);
        writeBufferPixel(x0 - varX, y0 + varY, 1);
        writeBufferPixel(x0 + varX, y0 - varY, 1);
        writeBufferPixel(x0 - varX, y0 - varY, 1);
        writeBufferPixel(x0 + varY, y0 + varX, 1);
        writeBufferPixel(x0 - varY, y0 + varX, 1);
        writeBufferPixel(x0 + varY, y0 - varX, 1);
        writeBufferPixel(x0 - varY, y0 - varX, 1);
        if(var1 < 0) {
            var1 = var1 + 4 * varX + 6;
        } else {
            var1 = var1 + 4 * (varX - varY) + 10;
            varY --;
        }
        varX ++;
    }
    regionalRefresh(x0-r, y0-r, 2*r+1, 2*r+1);
}

/**
  * @brief Fill a circle on the screen
  *
  * @param x0: Center x coordinate
  *
  * @param y0: Center y coordinate
  *
  * @param r: radius
  */
void DFRobot_SSD1306::fillCircle(int32_t x0, int32_t y0, int32_t r)
{
    r = abs(r);
    int16_t       varX = 0, varY = r;
    int16_t       endY = 0;
    int32_t       var1 = 3 - 2 * r;

    while(varX <= varY) {
        VLineOnePixel(x0+varX, y0-varY, 2 * varY + 1);
        VLineOnePixel(x0+varY, y0-varX, 2 * varX + 1);
        VLineOnePixel(x0-varX, y0-varY, 2 * varY + 1);
        VLineOnePixel(x0-varY, y0-varX, 2 * varX + 1);
        if(var1 < 0) {
            var1 = var1 + 4 * varX + 6;
        } else {
            var1 = var1 + 4 * (varX - varY) + 10;
            varY --;
        }
        varX ++;
    }
    regionalRefresh(x0-r, y0-r, 2*r+1, 2*r+1);
}

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
void DFRobot_SSD1306::fillScreenRange(int32_t line, int32_t column1, int32_t column2, uint32_t color)
{
    line = constrain(line, 0, 3);
    uint32_t c = getBrushColor();
    uint32_t fill_x1,fill_x2;
    uint32_t width;
    if(column1>column2){
        fill_x1 = column2;
        fill_x2 = column1;
    }else{
        fill_x1 = column1;
        fill_x2 = column2;
    }
    width = fill_x2-fill_x1; 
    setBrushColor(color);
    rect(column1, line*16 ,width, 16, true);
    setBrushColor(c);
}

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
void DFRobot_SSD1306::line(int32_t x0, int32_t y0, int32_t x1, int32_t y1)
{
    x0 = int(x0);
    y0 = int(y0);
    x1 = int(x1);
    y1 = int(y1);
    int x = int(x0);
    int y = int(y0);
    if(x == x1){
        VLine(x, y, y1 - y + 1);
    }else if(y == y1){
        HLine(x, y, x1 - x + 1);
    }else{
        uint8_t dx = abs(x1 - x);
        uint8_t dy = abs(y1 - y);
        int dirX = ternaryExpression(x < x1, 1, -1);
        int dirY = ternaryExpression(y < y1, 1, -1);
        int err;
        if(dx > dy){
            err = dx / 2;
            for(int i=0; i<dx; i++)
            {
                HLine(x, y, 1);
                x += dirX;
                err -= dy;
                if(err < 0)
                {
                    err += dx;
                    y += dirY;
                }
            }
            HLine(x1, y1, 1);
        }
        else
        {
            err = dy / 2;
            for(int i=0; i<dy; i++){
                VLine(x, y, 1);
                y += dirY;
                err -= dx;
                if(err < 0)
                {
                    err += dy;
                    x += dirX;
                }
            }
            VLine(x1, y1, 1);
        }
    }
    regionalRefresh(x0-brushWidth, y0-brushWidth, x1-x0+1+2*brushWidth, y1-y0+1+2*brushWidth);
}

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
void DFRobot_SSD1306::rect(int32_t x, int32_t y, int32_t width, int32_t height, bool fill)
{
    int backspace = brushWidth/2 + brushWidth%2 - 1;
    if(width < 0)
    {
        x += width;
        width = -width;
    }
    if(height < 0)
    {
        y += height;
        height = -height;
    }
    if(width == 0 && height == 0){
        return;
    }else if(width == 0){
        for(int i=0; i<brushWidth; i++) 
            VLineOnePixel(x-backspace+i, y-backspace, height+backspace*2);
    }else if(height == 0){
        for(int i=0; i<brushWidth; i++) 
            HLineOnePixel(x-backspace, y-backspace+i, width+backspace*2);
    }else if(fill){
        for(int i=0; i<height+2*backspace; i++)
            HLineOnePixel(x-backspace, y-backspace+i, width+backspace*2);
    }else{
        for(int i=0; i<brushWidth; i++) 
            HLineOnePixel(x-backspace, y-backspace+i, width+backspace*2);
        for(int i=0; i<brushWidth; i++) 
            HLineOnePixel(x-backspace, y+height-1-brushWidth/2+i, width+backspace*2);
        for(int i=0; i<brushWidth; i++) 
            VLineOnePixel(x-backspace+i, y-backspace, height+backspace*2);
        for(int i=0; i<brushWidth; i++) 
            VLineOnePixel(x+width-1-brushWidth/2+i, y-backspace, height+backspace*2);
    }
    regionalRefresh(x - backspace, y - backspace, width + backspace*2, height + backspace*2);
}

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
void DFRobot_SSD1306::drawImage(int32_t x, int32_t y, int32_t width, int32_t height, const uint8_t *image)
{
    if(width==0 && height==0 || !image) return;
    uint8_t _x = x, _y = y;

    for(uint8_t j=0; j<height; j++){
        if(_y > 63) break;
        for(uint8_t i=0; i<width/8; i++)
        {
            uint8_t data = *image;
            for(uint8_t k=0; k<8; k++)
            {
                if(_x>127) break;
                if(data & 0x80)
                    writeBufferPixel(_x,_y,1);
                else
                    writeBufferPixel(_x,_y,0);
                data = data << 1;
                _x++;
            }
            image++;
            if(!image) return;
        }
        if(width%8){
            uint8_t data = *image;
            for(uint8_t i=0; i<width%8; i++)
            {
                if(_x>127) break;
                if(data & 0x80)
                    writeBufferPixel(_x,_y,1);
                else
                    writeBufferPixel(_x,_y,0);
                data = data << 1;
                _x++;
            }
            image++;
            if(!image) return;
        }
        _y++;_x = x;
    }
    regionalRefresh(x, y, width, height);
}

/**
  * @brief Set the line width
  *
  * @param w: Pixel width
  *
  * @note Only for drawing lines and drawing rectangles
  */
void DFRobot_SSD1306::lineWidth(uint32_t w)
{
    w = w<1 ? 1 : w;
    brushWidth = w;
}

/**
  * @brief Draw a vertical line on the screen (One Pixe)
  *
  * @param x: Starting coordinate x
  *
  * @param y: Starting coordinate y
  *
  * @param height: height
  */
void DFRobot_SSD1306::VLineOnePixel(int16_t x, int16_t y, int16_t height)
{
    int8_t        direction = 1;
    int16_t       var1 = y + height;
    x = x < 0 ? 0 : x;
    x = x > 127 ? 127 : x;
    y = y < 0 ? 0 : y;
    y = y > 127 ? 127 : y;
    if(height < 0) {
        direction = -1;
    }
    for(; y != var1; y += direction) {
        writeBufferPixel(x, y, brushColor == 1 ? 1 : 0);
    }
}

/**
  * @brief Draw a horizontal line on the screen (One Pixe)
  *
  * @param x: Starting coordinate x
  *
  * @param y: Starting coordinate y
  *
  * @param width: width
  */
void DFRobot_SSD1306::HLineOnePixel(int16_t x, int16_t y, int16_t width)
{
    int8_t        direction = 1;
    int16_t       var1 = x + width;
    x = x < 0 ? 0 : x;
    x = x > 127 ? 127 : x;
    y = y < 0 ? 0 : y;
    y = y > 127 ? 127 : y;
    if(width < 0) {
        direction = -1;
    }
    for(; x != var1; x += direction) {
        writeBufferPixel(x, y, brushColor == 1 ? 1 : 0);
    }
}

/**
  * @brief Draw a vertical line on the screen
  *
  * @param x: Starting coordinate x
  *
  * @param y: Starting coordinate y
  *
  * @param height: height
  */
void DFRobot_SSD1306::VLine(int16_t x, int16_t y, int16_t height)
{
    x = int(x);
    y = int(y);
    height = int(height);
    int direction = getDirection(height);
    x -= brushWidth / 2;
    int x_offset;
    for (int i=0; i<ternaryExpression(height > 0, height, - height); i++)
    {
        x_offset = x;
        for(int j=0; j<brushWidth; j++)
        {
            writeBufferPixel(x_offset, y, brushColor == 1 ? 1 : 0);
            x_offset += 1;
        }
        y += direction;
    }
}

/**
  * @brief Draw a horizontal line on the screen
  *
  * @param x: Starting coordinate x
  *
  * @param y: Starting coordinate y
  *
  * @param width: width
  */
void DFRobot_SSD1306::HLine(int16_t x, int16_t y, int16_t width)
{
    x = int(x);
    y = int(y);
    width = int(width);
    int direction = getDirection(width);
    y -= brushWidth / 2;
    int y_offset;
    for(int i=0; i<ternaryExpression(width > 0, width, - width); i++)
    {
        y_offset = y;
        for(int j=0; j<brushWidth; j++)
        {
            writeBufferPixel(x, y_offset, brushColor == 1 ? 1 : 0);
            y_offset += 1;
        }
        x += direction;
    }
}

/**
  * @brief Draw a point in the screen cache
  *
  * @param x: Starting coordinate x
  *
  * @param y: Starting coordinate y
  *
  * @param color: color
  */
void DFRobot_SSD1306::writeBufferPixel(int16_t x, int16_t y, uint16_t color)
{
    if(x<0 || x>127 || y<0 || y>63) return;
    int16_t addr = x + y / 8 * 128;
    if(color == 1) {
        SSD1306_FrameBuffer[addr] |= 0x01 << (y % 8);
    } else {
        SSD1306_FrameBuffer[addr] &= ~ (0x01 << (y % 8));
    }
}

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
void DFRobot_SSD1306::regionalRefresh(int16_t x, int16_t y, int16_t width, int16_t height)
{
    int16_t xe = x+width-1;
    int16_t ye = y+height-1;

    if(x<0) x=0;
    if(x>127) x=127;
    if(y<0) y=0;
    if(y>63) y=63;

    if(xe<0) xe=0;
    if(xe>127) xe=127;
    if(ye<0) ye=0;
    if(ye>63) ye=63;

    int16_t data;
    if(xe < x) {
        data = xe;
        xe = x;
        x = data;
    }
    if(ye < y) {
        data = ye;
        ye = y;
        y = data;
    }
    width = xe - x + 1;
    height = ye - y + 1;

    int8_t widthSize = (xe-x+1)/16;
    int8_t widthSizeRemainder = (xe-x+1)%16;
    int8_t pageaddrLow = y/8;
    int8_t pageaddrHight = ye/8;

    for(uint8_t i=pageaddrLow; i<=pageaddrHight; i++)
    {
        setRefreshRange(this->address, SSD1306_WRITECMD, x, x + width - 1, i, i);
        uint8_t j;
        for(j = 0; j < widthSize; j++)
        {
            writeBuffer(this->address, SSD1306_WRITEDATA, SSD1306_FrameBuffer + i*128 + x + j*16, 16);
        }
        if(widthSizeRemainder)
        {
            writeBuffer(this->address, SSD1306_WRITEDATA, SSD1306_FrameBuffer + i*128 + x + j*16, widthSizeRemainder);
        }
    }
}
#endif






