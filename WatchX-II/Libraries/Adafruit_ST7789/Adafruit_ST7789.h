#ifndef __ADAFRUIT_ST7789_H
#define __ADAFRUIT_ST7789_H

#include "Adafruit_GFX_Library/Adafruit_GFX.h"


#define ST7789_TFTWIDTH  240
#define ST7789_TFTHEIGHT 240

#if defined(__STM32__)
typedef volatile uint32_t PortReg_t;
#define USE_FAST_IO
#elif defined(__AVR__)
typedef volatile uint8_t PortReg_t;
#define USE_FAST_IO
#endif

class Adafruit_ST7789 : public Adafruit_GFX
{
public:
    Adafruit_ST7789(
        uint8_t port_start, uint8_t rst, uint8_t cs, 
        uint8_t rs, uint8_t rw, uint8_t rd
    );

    typedef enum
    {
        White = 0xFFFF,
        Black = 0x0000,
        Blue = 0x001F,
        Blue2 = 0x051F,
        Red = 0xF800,
        Magenta = 0xF81F,
        Green = 0x07E0,
        Transparent = 0x07E0,
        Cyan = 0x7FFF,
        Yellow = 0xFFE0
    } Color_Type;

    void begin();
    uint8_t PORT_READ();
    void read(uint8_t cmd, void *dat, int len);
    void writeCommand(uint8_t cmd);
    void writeData(uint8_t data);
    void writeData16(uint16_t data);
    void readCommand(uint8_t command, void *dat, int len);

    virtual void drawPixel(int16_t x, int16_t y, uint16_t color);
    virtual void setAddrWindow(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    virtual void setCursor(int16_t x, int16_t y);
    virtual void setRotation(uint8_t r);
    virtual void fillScreen(uint16_t color);
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    virtual void drawRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h);
    virtual void drawFastRGBBitmap(int16_t x, int16_t y, uint16_t *bitmap, int16_t w, int16_t h);
    virtual void inline pushColor(uint16_t color)
    {
        writeData16(color);
    }
    // Pass 8-bit (each) R,G,B, get back 16-bit packed color
    uint16_t color565(uint8_t r, uint8_t g, uint8_t b) {
        return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
    }

private:
    PortReg_t* TFT_Port;
    uint8_t PORT_START; 
    uint8_t RST, CS, RS, RW, RD;
    uint8_t colstart, rowstart, xstart, ystart;

#if defined(USE_FAST_IO)
    #if defined(__AVR__) || defined(CORE_TEENSY)
        volatile uint8_t *rstport, *csport, *rsport, *rwport, *rdport;
        uint8_t  rstpinmask, cspinmask, rspinmask, rwpinmask, rdpinmask;
    #elif defined(__STM32__) 
        GPIO_TypeDef *rstport, *csport, *rsport, *rwport, *rdport;
        uint16_t  rstpinmask, cspinmask, rspinmask, rwpinmask, rdpinmask;
    #else
        volatile uint32_t *rstport, *csport, *rsport, *rwport, *rdport;
        uint32_t  rstpinmask, cspinmask, rspinmask, rwpinmask, rdpinmask;
    #endif
#endif
};

#endif
