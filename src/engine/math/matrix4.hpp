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

#ifndef FR_MATH_MATRIX4_HPP
#define FR_MATH_MATRIX4_HPP

#include "vectors.hpp"

#include "basic_functions.hpp"

#define SIZE 4

namespace fr::math {  
    class Matrix4 {
        public:
            Matrix4();
            Matrix4(float e00, float e01, float e02, float e03,
                    float e10, float e11, float e12, float e13,
                    float e20, float e21, float e22, float e23,
                    float e30, float e31, float e32, float e33);

            void Zero();
            void Identity();
            void Identity(float s);
            void SetTranslation(float x, float y, float z);
            void SetScale(float x, float y, float z);
            void SetRotationX(float x);
            void SetRotationY(float y);
            void SetRotationZ(float z);

            Matrix4 operator+(Matrix4 matrix);
            Matrix4 operator-(Matrix4 matrix);
            Matrix4 operator/(Matrix4 matrix);
            Matrix4 operator*(Matrix4 matrix);
            void SetOrtho(float left, float right, float bottom, float top, float m_near, float m_far);
            void SetPerspective(float fov, float aspectRatio, float m_near, float m_far);

            static Matrix4 createTranslation(const Vector3 &v);
            static Matrix4 createTranslation(float x, float y, float z);
            static Matrix4 createScale(const Vector3 &v);
            static Matrix4 createScale(float x, float y, float z);
            static Matrix4 createRotationX(float a);
            static Matrix4 createRotationY(float a);
            static Matrix4 createRotationZ(float a);
            static Matrix4 createRotation(float a, const Vector3& v);
            static Matrix4 createLookAt(const Vector3& eye, const Vector3& center, const Vector3& up);
            static Matrix4 createPerspective(float fovy, float aspect, float near, float far);
            static Matrix4 Inverse();

            float* ToPointer() {
                return &Matrix[0][0];
            }

            const float* ToPointer() const {
                return &Matrix[0][0];
            }

        private:
            float Matrix[SIZE][SIZE];
    };
}

#endif // FR_MATH_MATRIX4_HPP