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

#ifndef FR_MATH_VECTORS_HPP
#define FR_MATH_VECTORS_HPP

#include "basic_functions.hpp"

namespace fr::math {  
     class Vector4 {
        public:
        Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
        Vector4(float X,float Y,float Z,float W) : x(X), y(Y), z(Z), w(W) {}
        Vector4(float number) : x(number), y(number), z(number), w(number) {}
        Vector4(const Vector4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

        float Length() { return sqrt(x*x + y*y + z*z + w*w); }

        Vector4 operator+(const Vector4& other) { return Vector4(x + other.x, y + other.y, z + other.z, w + other.w); }
        Vector4 operator+(float other) { return Vector4(x + other, y + other, z + other, w + other); }
         
        Vector4 operator-(const Vector4& other) { return Vector4(x - other.x, y - other.y, z - other.z, w - other.w); }
        Vector4 operator-(float other) { return Vector4(x - other, y - other, z - other, w - other); }

        Vector4 operator/(const Vector4& other) { return Vector4(x / other.x, y / other.y, z / other.z, w / other.w); }
        Vector4 operator/(float other) { return Vector4(x / other, y / other, z / other, w / other); }

        Vector4 operator*(const Vector4& other) { return Vector4(x * other.x, y * other.y, z * other.z, w * other.w); }
        Vector4 operator*(float other) { return Vector4(x * other, y * other, z * other, w * other); }

        void operator=(float other) { x = other; y = other; z = other; w = other; }
        void operator=(Vector4 other) { x = other.x; y = other.y; z = other.z; w = other.w; }

        bool operator==(Vector4 other) { return (x == other.x && y == other.y && z == other.z && w == other.w); }
        bool operator!=(Vector4 other) { return (x != other.x && y != other.y && z != other.z && z != other.w); }

        void operator+=(Vector4 other) { x += other.x; y += other.y; z += other.z; w += other.w;}
        void operator-=(Vector4 other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w;}

        void operator*=(Vector4 other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w;}

        void operator/=(Vector4 other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w;}
        void operator/=(float other) { x /= other; y /= other; z /= other; w /= other;}

        float x,y,z,w;        
        
        Vector4 Normalized_q_rsqrt() {
            Vector4 n = *this;
            return n * q_rsqrt(x*x + y*y + z*z + w*w);
        }

        Vector4 Normalized() {
            Vector4 n = *this;
            return n / Length();
        }
    }; 

    class Vector3 {
        public:
        Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vector3(float X,float Y,float Z) : x(X), y(Y), z(Z) {}
        Vector3(float number) : x(number), y(number), z(number) {}
        Vector3(const Vector3& other) : x(other.x), y(other.y), z(other.z) {}

        float Length() { return sqrt(x*x + y*y + z*z); }

        Vector3 operator+(const Vector3& other) { return Vector3(x + other.x, y + other.y, z + other.z); }
        Vector3 operator+(float other) { return Vector3(x + other, y + other, z + other); }
         
        Vector3 operator-(const Vector3& other) { return Vector3(x - other.x, y - other.y, z - other.z); }
        Vector3 operator-(float other) { return Vector3(x - other, y - other, z - other); }

        Vector3 operator/(const Vector3& other) { return Vector3(x / other.x, y / other.y, z / other.z); }
        Vector3 operator/(float other) { return Vector3(x / other, y / other, z / other); }

        Vector3 operator*(const Vector3& other) { return Vector3(x * other.x, y * other.y, z * other.z); }
        Vector3 operator*(float other) { return Vector3(x * other, y * other, z * other); }

        void operator=(float other) { x = other; y = other; z = other; }
        void operator=(Vector3 other) { x = other.x; y = other.y; z = other.z; }

        bool operator==(Vector3 other) { return (x == other.x && y == other.y && z == other.z); }
        bool operator!=(Vector3 other) { return (x != other.x && y != other.y && z != other.z); }

        void operator+=(Vector3 other) { x += other.x; y += other.y; z += other.z; }
        void operator-=(Vector3 other) { x -= other.x; y -= other.y; z -= other.z; }

        void operator*=(Vector3 other) { x *= other.x; y *= other.y; z *= other.z; }

        void operator/=(Vector3 other) { x /= other.x; y /= other.y; z /= other.z; }
        void operator/=(float other) { x /= other; y /= other; z /= other; }

        float x,y,z;        
        
        Vector3 Normalized_q_rsqrt() {
            Vector3 n = *this;
            return n * q_rsqrt(x*x + y*y + z*z);
        }

        Vector3 Normalized() {
            Vector3 n = *this;
            return n / Length();
        }
    }; 

    class Vector2 {
        public:
        Vector2() : x(0.0f), y(0.0f) {}
        Vector2(const float _x, const float _y) : x(_x), y(_y) {}
        Vector2(float number) : x(number), y(number) {}
        Vector2(const Vector2& other) : x(other.x), y(other.y) {}
        ~Vector2() = default;

        float Length() { return sqrt(x*x + y*y); }

        const Vector2 operator+(const Vector2& other) { return Vector2(x + other.x, y + other.y); }
        const Vector2 operator+(float other) { return Vector2(x + other, y + other); }
         
        const Vector2 operator-(const Vector2& other) { return Vector2(x - other.x, y - other.y); }
        const Vector2 operator-(float other) { return Vector2(x - other, y - other); }

        const Vector2 operator/(Vector2 other) { return Vector2(x / other.x, y / other.y); }
        const Vector2 operator/(float other) { return Vector2(x / other, y / other); }

        const Vector2 operator*(const Vector2& other) { return Vector2(x * other.x, y * other.y); }
        const Vector2 operator*(float other) { return Vector2(x * other, y * other); }

        void operator=(float other) { x = other; y = other; }
        void operator=(Vector2 other) { x = other.x; y = other.y; }

        bool operator==(Vector2 other) { return (x == other.x && y == other.y ); }
        bool operator!=(Vector2 other) { return (x != other.x && y != other.y ); }

        void operator+=(Vector2 other) { x += other.x; y += other.y; }
        void operator-=(Vector2 other) { x -= other.x; y -= other.y; }

        void operator*=(Vector2 other) { x *= other.x; y *= other.y; }

        void operator/=(Vector2 other) { x /= other.x; y /= other.y; }
        void operator/=(float other) { x /= other; y /= other; }

        float x,y;        
        
        Vector2 Normalized_q_rsqrt() {
            Vector2 n = *this;
            return n * q_rsqrt(x*x + y*y);
        }

        Vector2 Normalized() {
            Vector2 n = *this;
            return n / Length();
        }
    };
}

#endif // FR_MATH_VECTORS_HPP