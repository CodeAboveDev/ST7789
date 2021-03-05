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
    SleepOut();
    SetColorMode();
    InversionOn();
    DisplayOn();
    SetScreenSize(240, 240);

    SendTestData();
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
    WriteCommand(Command::SoftwareReset);
    Wait(120);
}

void ST7789::SleepOut(void)
{
    WriteCommand(Command::SleepOut);
    Wait(120);
}

void ST7789::InversionOn(void)
{
    WriteCommand(Command::InversionOn);
}

void ST7789::DisplayOn(void)
{
    WriteCommand(Command::DisplayOn);
}

void ST7789::SetColorMode(void)
{
    WriteCommand(Command::InterfacePixelFormat);
    WriteData(0x55);
}

void ST7789::SetScreenSize(uint16_t height, uint16_t width)
{
    WriteCommand(Command::ColumnAddressSet);
    WriteData(0x00);
    WriteData(0x00);
    WriteData(((width-1) >> 8) & 0xFF);
    WriteData((width-1) & 0xFF);
    WriteCommand(Command::RowAddressSet);
    WriteData(0x00);
    WriteData(0x00);
    WriteData(((height-1) >> 8) & 0xFF);
    WriteData((height-1) & 0xFF);
}

void ST7789::Wait(uint32_t ms)
{
    uint32_t endTime = Timer_ms + ms;

    while(Timer_ms < endTime)
    {
        // Wait for them time to pass
    }
}

void ST7789::SendTestData(void)
{   
    uint16_t RGB565 = 0x07E0;
    uint16_t RGB565_2 = 0xE463;
    uint16_t RGB565_3  = 0xF800;

    WriteCommand(Command::MemoryWrite);

    for(uint32_t i = 0u; i < 57600; i++)
    {
        WriteData(RGB565 >> 8);
        WriteData(RGB565 & 0xFF);
    }    
    
    WriteCommand(Command::MemoryWrite);

    for(uint32_t i = 0u; i < 57600; i++)
    {
        WriteData(RGB565_2 >> 8);
        WriteData(RGB565_2 & 0xFF);
    }
    for(uint32_t i = 0u; i < 57600; i++)
    {
        WriteData(RGB565_3 >> 8);
        WriteData(RGB565_3 & 0xFF);
    }
}

void ST7789::WriteData(uint8_t data)
{
    dataCommandPin.Set();
    spi.Write(data);
}

void ST7789::WriteData(const uint8_t* buffer, size_t size)
{
    dataCommandPin.Set();
    spi.Write(buffer, size);
}

void ST7789::WriteCommand(Command command)
{
    dataCommandPin.Reset();
    spi.Write(etoi(command));
}
