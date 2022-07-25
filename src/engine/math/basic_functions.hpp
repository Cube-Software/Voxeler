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

#ifndef FR_MATH_BASIC_FUNCTIONS_HPP
#define FR_MATH_BASIC_FUNCTIONS_HPP

#define PI 3.14159265359

namespace fr::math{
    extern float Sqrt(float x);
    extern float q_rsqrt(float x);
    extern float Power(float x, float y);
    extern float Abs(float x);
    extern float Abs(int x);
    extern float Cos(float x);
    extern float Acos(float x);
    extern float Sin(float x);
    extern float Asin(float x);
    extern float Tan(float x);
    extern float Atan(float x);
    extern float Atan2(float y, float x);
    extern int RandomRange(int max);
    extern int RandomRange(int min, int max);
    extern float RandomRangef(float max);
    extern float RandomRangef(float min, float max);
    extern float rad2deg(float rad);
    extern float deg2rad(float deg);
}

#endif // FR_MATH_BASIC_FUNCTIONS_HPP