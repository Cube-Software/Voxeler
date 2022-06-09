#pragma once

#define PI 3.14159265359

namespace fr::math{
    extern float sqrt(float number);
    extern float q_rsqrt(float number);

    extern float power(float base, int exp);
    extern int fact(int n);

    extern float abs(float number);
    extern float abs(int number);

    extern float cosine(int deg);
    extern float sine(int deg);
    extern float tangent(int deg);
    extern float cotangent(int deg);

    extern float rad2deg(float rad);
    extern float deg2rad(float deg);
}