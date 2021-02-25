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

class IPin
{
public:
    virtual void Set(void) = 0;
    virtual void Reset(void) = 0;
};

class IST7789Spi
{
public:
    virtual void Write(const uint8_t byte) = 0;
};

class ST7789
{
public:
    ST7789(IST7789Spi& spi, IPin& rstPin, IPin& dcPin);

    static void Task1ms(void);

    void Reset(void);

private:
    static constexpr uint8_t MinimumResetPulseTime_ms { 10u };
    static constexpr uint8_t MaximumBlankingTime_ms { 120u };

    IPin& resetPin;
    IPin& dataCommandPin;
    IST7789Spi& spi;



    volatile static uint32_t Timer_ms;

    void Wait(uint32_t ms);
    

};

#endif // ST7789_H