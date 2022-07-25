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

#include "quaternion.hpp"

namespace fr::math {
    Quaternion::Quaternion(float x, float y, float z, float w) {
        (*this).x = x;
        (*this).y = y;
        (*this).z = z;
        (*this).w = w;
    }

    Quaternion::Quaternion(Vector4 m) {
        (*this).x = m.x;
        (*this).y = m.y;
        (*this).z = m.z;
        (*this).w = m.w;
    }

    Quaternion::Quaternion(Vector3 axis, float angle) {
        float HalfSin = Sin(angle / 2);
        float HalfCos = Cos(angle / 2);
        (*this).x = axis.x * HalfSin;
        (*this).y = axis.y * HalfSin;
        (*this).z = axis.z * HalfSin;
        (*this).w = HalfCos;
    }

    Quaternion Quaternion::operator=(Quaternion q) { x = q.x; y = q.y; z = q.z; w = q.w; return *this; }
    Quaternion Quaternion::operator+(Quaternion q) { x + q.x; y + q.y; z + q.z; w + q.w; return *this; }
    Quaternion Quaternion::operator-(Quaternion q) { x - q.x; y - q.y; z - q.z; w - q.w; return *this; }
    Quaternion Quaternion::operator/(Quaternion q) { x / q.x; y / q.y; z / q.z; w / q.w; return *this; }
    Quaternion Quaternion::operator*(Quaternion q) { x * q.x; y * q.y; z * q.z; w * q.w; return *this; }
    Quaternion Quaternion::operator+=(Quaternion q) { x += q.x; y += q.y; z += q.z; w += q.w; return *this; }
    Quaternion Quaternion::operator-=(Quaternion q) { x -= q.x; y -= q.y; z -= q.z; w -= q.w; return *this; }
    Quaternion Quaternion::operator/=(Quaternion q) { x /= q.x; y /= q.y; z /= q.z; w /= q.w; return *this; }
    Quaternion Quaternion::operator*=(Quaternion q) { x *= q.x; y *= q.y; z *= q.z; w *= q.w; return *this; }
              
    Quaternion Quaternion::operator=(float q) { x = q; y = q; z = q; w = q; return *this; }
    Quaternion Quaternion::operator+(float q) { x + q; y + q; z + q; w + q; return *this; }
    Quaternion Quaternion::operator-(float q) { x - q; y - q; z - q; w - q; return *this; }
    Quaternion Quaternion::operator/(float q) { x / q; y / q; z / q; w / q; return *this; }
    Quaternion Quaternion::operator*(float q) { x * q; y * q; z * q; w * q; return *this; }
    Quaternion Quaternion::operator+=(float q) { x += q; y += q; z += q; w += q; return *this; }
    Quaternion Quaternion::operator-=(float q) { x -= q; y -= q; z -= q; w -= q; return *this; }
    Quaternion Quaternion::operator/=(float q) { x /= q; y /= q; z /= q; w /= q; return *this; }
    Quaternion Quaternion::operator*=(float q) { x *= q; y *= q; z *= q; w *= q; return *this; }

    
    void Quaternion::normalize() {
        if (norm()!=0) {
            float nV=1/norm();
    
            x *= nV;
            y *= nV;
            z *= nV;
            w *= nV;
        }
    }

    float Quaternion::norm() { 
        float scalar = w*w;
        float img = x*x + y*y + z*z;

        return Sqrt(scalar + img);
    }

    void Quaternion::Convert2Unit() {
        float angle=deg2rad(w);
        x * q_rsqrt(x*x + y*y + z*z);
        y * q_rsqrt(x*x + y*y + z*z);  // Fast Inverse Square root :P
        z * q_rsqrt(x*x + y*y + z*z);

        w=Cos(angle*0.5);

        x=x*Sin(angle*0.5);
        y=y*Sin(angle*0.5);
        z=z*Sin(angle*0.5);
    }

    Quaternion Quaternion::conjugate() {
        Vector3 img = Vector3(x,y,z) *(-1);
        return Quaternion(img , w);
    }

    Quaternion Quaternion::inverse() {
        float AValue=norm();
        AValue*=AValue;
        AValue=1/AValue;
        
        Quaternion conjugateValue=conjugate();
        
        float scalar=conjugateValue.w*(AValue);
        Vector3 imaginary= Vector3(conjugateValue.x, conjugateValue.y, conjugateValue.z) *(AValue);
        
        return Quaternion(imaginary, scalar);
    }
}