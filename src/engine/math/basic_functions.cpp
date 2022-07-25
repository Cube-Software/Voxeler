/*
    Fractal Engine - OpenGL 3D Game Engine
    Created by CubeSoftware
    Revised for Voxeler

    -------------------------------
    Copyright (c) 2021-2022 CubeSoftware
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "basic_functions.hpp"
#include "../core/random.hpp"

#include <math.h>

namespace fr::math {
    float q_rsqrt(float x) {  
        // Fast inverse square root from Quake III: Arena
        long i;
        float x2, y;
        const float threehalfs = 1.5F;

        x2 = x * 0.5F;
        y  = x;
        i  = * ( long * ) &y;                      
        i  = 0x5f3759df - ( i >> 1 );               // wtf?
        y  = * ( float * ) &i;
        y  = y * ( threehalfs - ( x2 * y * y ) );  

        return y;
    }

    float rad2deg(float rad) { return rad * 180 / PI; }
    float deg2rad(float deg) { return deg * PI / 180; }

    float Sqrt(float x) { return ::sqrtf(x); }
    float Power(float x, float y) { return ::powf(x, y); }
    float Abs(float x) { return ::fabsf(x); }
    float Abs(int x) { return x < 0 ? (float)-x : (float)x; }
    float Cos(float x) { return ::cosf(x); }
    float Acos(float x) { return ::acosf(x); }
    float Sin(float x) { return ::sinf(x); }
    float Asin(float x) { return ::asinf(x); }
    float Tan(float x) { return ::tanf(x); }
    float Atan(float x) { return ::atanf(x); }
    float Atan2(float y, float x) { return ::atan2f(y, x); }

    int RandomRange(int max) { return core::g_RandomDevice.get_number() % max; }
    int RandomRange(int min, int max) { return min + core::g_RandomDevice.get_number() % (max - min); }
    float RandomRangef(float max) { return max * float(core::g_RandomDevice.get_number() / core::g_RandomDevice.get_max_value()); }
    float RandomRangef(float min, float max) { return min + (max - min) * float(core::g_RandomDevice.get_number() / core::g_RandomDevice.get_max_value()); }

}