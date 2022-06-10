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
        float HalfSin = sine(angle / 2);
        float HalfCos = cosine(angle / 2);
        (*this).x = axis.x * HalfSin;
        (*this).y = axis.y * HalfSin;
        (*this).z = axis.z * HalfSin;
        (*this).w = HalfCos;
    }

    Quaternion Quaternion::operator=(Quaternion q) { x = q.x; y = q.y; z = q.z; w = q.w; }
    Quaternion Quaternion::operator+(Quaternion q) { x + q.x; y + q.y; z + q.z; w + q.w; }
    Quaternion Quaternion::operator-(Quaternion q) { x - q.x; y - q.y; z - q.z; w - q.w; }
    Quaternion Quaternion::operator/(Quaternion q) { x / q.x; y / q.y; z / q.z; w / q.w; }
    Quaternion Quaternion::operator*(Quaternion q) { x * q.x; y * q.y; z * q.z; w * q.w; }
    Quaternion Quaternion::operator+=(Quaternion q) { x += q.x; y += q.y; z += q.z; w += q.w; }
    Quaternion Quaternion::operator-=(Quaternion q) { x -= q.x; y -= q.y; z -= q.z; w -= q.w; }
    Quaternion Quaternion::operator/=(Quaternion q) { x /= q.x; y /= q.y; z /= q.z; w /= q.w; }
    Quaternion Quaternion::operator*=(Quaternion q) { x *= q.x; y *= q.y; z *= q.z; w *= q.w; }

    Quaternion Quaternion::operator=(float q) { x = q; y = q; z = q; w = q; }
    Quaternion Quaternion::operator+(float q) { x + q; y + q; z + q; w + q; }
    Quaternion Quaternion::operator-(float q) { x - q; y - q; z - q; w - q; }
    Quaternion Quaternion::operator/(float q) { x / q; y / q; z / q; w / q; }
    Quaternion Quaternion::operator*(float q) { x * q; y * q; z * q; w * q; }
    Quaternion Quaternion::operator+=(float q) { x += q; y += q; z += q; w += q; }
    Quaternion Quaternion::operator-=(float q) { x -= q; y -= q; z -= q; w -= q; }
    Quaternion Quaternion::operator/=(float q) { x /= q; y /= q; z /= q; w /= q; }
    Quaternion Quaternion::operator*=(float q) { x *= q; y *= q; z *= q; w *= q; }

    
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

        return sqrt(scalar + img);
    }

    void Quaternion::Convert2Unit() {
        float angle=deg2rad(w);
        x * q_rsqrt(x*x + y*y + z*z);
        y * q_rsqrt(x*x + y*y + z*z);  // Fast Inverse Square root :P
        z * q_rsqrt(x*x + y*y + z*z);

        w=cosine(angle*0.5);

        x=x*sine(angle*0.5);
        y=y*sine(angle*0.5);
        z=z*sine(angle*0.5);
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