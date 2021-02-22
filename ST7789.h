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

class IPin
{
public:
    virtual void Set(void) = 0;
    virtual void Reset(void) = 0;
};

class ST7789
{
public:


private:


};

#endif // ST7789_H