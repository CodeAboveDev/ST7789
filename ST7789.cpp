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
#include "ST7789.h"

#include <type_traits>

template <typename E>
constexpr auto etoi(E const value)
{
    return static_cast<std::underlying_type_t<E>>(value);
}

volatile uint32_t ST7789::Timer_ms { 0u };

ST7789::ST7789(IST7789Spi& spi, IST7789Pin& rstPin, IST7789Pin& dcPin)
: spi(spi), resetPin(rstPin), dataCommandPin(dcPin)
{

}

void ST7789::Task1ms(void)
{
    Timer_ms++;
}

void ST7789::Init(void)
{
    Reset();
    SoftwareReset();
}

void ST7789::Reset(void)
{
    resetPin.Reset();
    Wait(MinimumResetPulseTime_ms);
    resetPin.Set();
    Wait(MaximumBlankingTime_ms);
}

void ST7789::SoftwareReset(void)
{
    dataCommandPin.Reset();
    spi.Write(static_cast<std::underlying_type_t<Command>>(Command::SoftwareReset));
    Wait(120);
    dataCommandPin.Set();
}

void ST7789::Wait(uint32_t ms)
{
    uint32_t endTime = Timer_ms + ms;

    while(Timer_ms < endTime)
    {
        // Wait for them time to pass
    }
}
void ST7789::WriteData(uint8_t data)
{
    dataCommandPin.Set();
    spi.Write(data);
}

void ST7789::WriteCommand(Command command)
{
    dataCommandPin.Reset();
    spi.Write(etoi(command));
}
