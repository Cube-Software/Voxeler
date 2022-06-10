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