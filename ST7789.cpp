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

volatile uint32_t ST7789::Timer_ms { 0u };

ST7789::ST7789(IPin& rstPin, IPin& dcPin)
: resetPin(rstPin), dataCommandPin(dcPin)
{

}

void ST7789::Task1ms(void)
{
    Timer_ms++;
}

void ST7789::Reset(void)
{
    resetPin.Reset();
    Wait(MinimumResetPulseTime_ms);
    resetPin.Set();
    Wait(MaximumBlankingTime_ms);
}

void ST7789::Wait(uint32_t ms)
{
    uint32_t endTime = Timer_ms + ms;

    while(Timer_ms < endTime)
    {
        // Wait for them time to pass
    }
}
