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

#pragma once

#include "vectors.hpp"
#include "basic_functions.hpp"

namespace fr::math {
    class Quaternion{
        public:
            Quaternion() = default;
            ~Quaternion() = default;

            Quaternion(float x, float y, float z, float w);
            Quaternion(Vector4 m);
            Quaternion(Vector3 axis, float angle);

            // operators 
            Quaternion operator=(Quaternion q);
            Quaternion operator+(Quaternion q);
            Quaternion operator-(Quaternion q);
            Quaternion operator/(Quaternion q);
            Quaternion operator*(Quaternion q);
            Quaternion operator+=(Quaternion q);
            Quaternion operator-=(Quaternion q);
            Quaternion operator/=(Quaternion q);
            Quaternion operator*=(Quaternion q);
            Quaternion operator=(float q);
            Quaternion operator+(float q);
            Quaternion operator-(float q);
            Quaternion operator/(float q);
            Quaternion operator*(float q);   
            Quaternion operator+=(float q);
            Quaternion operator-=(float q);
            Quaternion operator/=(float q);
            Quaternion operator*=(float q);

            void normalize();
            float norm();
            void Convert2Unit();
            void Show();

            Quaternion conjugate();

            Quaternion inverse();
            Quaternion inverse(Quaternion& q);

            float x;
            float y; // vector
            float z;

            float w; // scalar
    };
}