/*****************************************************************
 * Copyright (c) 2021 CodeAbove.
 * All rights reserved.
 *
 * This software component is licensed by CodeAbove under
 * BSD 3-Clause license, the 'License'. You may not use
 * this file except in compliance with the License. You
 * may obtain a copy of the License at:
 *                  opensource.org/licenses/BSD-3-Clause
 ****************************************************************/
#ifndef ST7789_H
#define ST7789_H

#include <stdint.h>
#include <stdlib.h>

class IST7789Pin
{
public:
    virtual void Set(void) = 0;
    virtual void Reset(void) = 0;
};

class IST7789Spi
{
public:
    virtual void Write(const uint8_t byte) = 0;
    virtual void Write(const uint8_t* buffer, size_t size) = 0;
};

class ST7789
{
public:
    ST7789(IST7789Spi& spi, IST7789Pin& rstPin, IST7789Pin& dcPin, uint8_t* buf);

    static void Task1ms(void);

    void Init(void);
    void RefreshDisplay(void);
    void SetPixel(int16_t x, int16_t y, uint16_t color);
private:
    enum class Command : uint8_t
    {
        SoftwareReset           = 0x01,
        SleepOut                = 0x11,
        InversionOn             = 0x21,
        DisplayOn               = 0x29,
        ColumnAddressSet        = 0x2A,
        RowAddressSet           = 0x2B,
        MemoryWrite             = 0x2C,
        InterfacePixelFormat    = 0x3A,
        WriteMemoryContinue     = 0x3C,
    };

    static constexpr uint8_t MinimumResetPulseTime_ms { 10u };
    static constexpr uint8_t MaximumBlankingTime_ms { 120u };

    IST7789Spi& spi;
    IST7789Pin& resetPin;
    IST7789Pin& dataCommandPin;
    uint8_t* buffer;

    volatile static uint32_t Timer_ms;

    void Reset(void);
    void SoftwareReset(void);
    void SleepOut(void);
    void InversionOn(void);
    void DisplayOn(void);
    void SetWindow(void);
    void SetColorMode(void);
    void SetScreenSize(uint16_t height, uint16_t width);
    void Wait(uint32_t ms);  

    void SendTestData(void);

    void WriteData(uint8_t data);
    void WriteData(const uint8_t* data, size_t size);
    void WriteCommand(Command command);

};

#endif // ST7789_H