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

#include "matrix4.hpp"

namespace fr::math {
    Matrix4::Matrix4() { Zero(); }

    Matrix4::Matrix4(float e00, float e01, float e02, float e03, float e10, float e11, float e12, float e13, float e20, float e21, float e22, float e23, float e30, float e31, float e32, float e33) {
        Matrix[0][0] = e00; Matrix[0][1] = e01; Matrix[0][2] = e02; Matrix[0][3] = e03;
        Matrix[1][0] = e10; Matrix[1][1] = e11; Matrix[1][2] = e12; Matrix[1][3] = e13;
        Matrix[2][0] = e20; Matrix[2][1] = e21; Matrix[2][2] = e22; Matrix[2][3] = e23;
        Matrix[3][0] = e30; Matrix[3][1] = e31; Matrix[3][2] = e32; Matrix[3][3] = e33;
    }

    void Matrix4::Zero(){
        for(int x = 0; x < 4; x++) {
            for(int y = 0; y < 4; y++) {
                Matrix[x][y] = 0;
            }
        }
    }

    void Matrix4::Identity() {
        Matrix[0][0] = 1; Matrix[0][1] = 0; Matrix[0][2] = 0; Matrix[0][3] = 0;
        Matrix[1][0] = 0; Matrix[1][1] = 1; Matrix[1][2] = 0; Matrix[1][3] = 0;
        Matrix[2][0] = 0; Matrix[2][1] = 0; Matrix[2][2] = 1; Matrix[2][3] = 0;
        Matrix[3][0] = 0; Matrix[3][1] = 0; Matrix[3][2] = 0; Matrix[3][3] = 1;
    }    

    void Matrix4::Identity(float s){
        Matrix[0][0] = s; Matrix[0][1] = 0; Matrix[0][2] = 0; Matrix[0][3] = 0;
        Matrix[1][0] = 0; Matrix[1][1] = s; Matrix[1][2] = 0; Matrix[1][3] = 0;
        Matrix[2][0] = 0; Matrix[2][1] = 0; Matrix[2][2] = s; Matrix[2][3] = 0;
        Matrix[3][0] = 0; Matrix[3][1] = 0; Matrix[3][2] = 0; Matrix[3][3] = s;
    }            
    
    void Matrix4::SetTranslation(float x, float y, float z) {
        Matrix[0][3] = x;
        Matrix[1][3] = y;
        Matrix[2][3] = z;
    }

    void Matrix4::SetScale(float x, float y, float z) {
        Matrix[0][0] = x;
        Matrix[1][1] = y;
        Matrix[2][2] = z;
    }

    void Matrix4::SetRotationX(float x) {
        float r = deg2rad(x);
        float c = Cos(r);
        float s = Sin(r);

        Matrix[1][1] = c;
        Matrix[1][2] = -s;
        Matrix[2][1] = s;
        Matrix[2][2] = c;
    }

    void Matrix4::SetRotationY(float y) {
        float r = deg2rad(y);
        float c = Cos(r);
        float s = Sin(r);

        Matrix[0][0] = c;
        Matrix[0][2] = s;
        Matrix[2][0] = -s;
        Matrix[2][2] = c;
    }

    void Matrix4::SetRotationZ(float z) {
        float r = deg2rad(z);
        float c = Cos(r);
        float s = Sin(r);

        Matrix[0][0] = c;
        Matrix[0][1] = -s;
        Matrix[1][0] = s;
        Matrix[1][1] = c;
    }

    Matrix4 Matrix4::operator+(Matrix4 matrix) {
        return Matrix4(Matrix[0][0] + matrix.Matrix[0][0], Matrix[0][1] + matrix.Matrix[0][1], Matrix[0][2] + matrix.Matrix[0][2], Matrix[0][3] + matrix.Matrix[0][3],
                        Matrix[1][0] + matrix.Matrix[1][0], Matrix[1][1] + matrix.Matrix[1][1], Matrix[1][2] + matrix.Matrix[1][2], Matrix[1][3] + matrix.Matrix[1][3],
                        Matrix[2][0] + matrix.Matrix[2][0], Matrix[2][1] + matrix.Matrix[2][1], Matrix[2][2] + matrix.Matrix[2][2], Matrix[2][3] + matrix.Matrix[2][3],
                        Matrix[3][0] + matrix.Matrix[3][0], Matrix[3][1] + matrix.Matrix[3][1], Matrix[3][2] + matrix.Matrix[3][2], Matrix[3][3] + matrix.Matrix[3][3]);
    }

    Matrix4 Matrix4::operator-(Matrix4 matrix) {
        return Matrix4(Matrix[0][0] - matrix.Matrix[0][0], Matrix[0][1] - matrix.Matrix[0][1], Matrix[0][2] - matrix.Matrix[0][2], Matrix[0][3] - matrix.Matrix[0][3],
                        Matrix[1][0] - matrix.Matrix[1][0], Matrix[1][1] - matrix.Matrix[1][1], Matrix[1][2] - matrix.Matrix[1][2], Matrix[1][3] - matrix.Matrix[1][3],
                        Matrix[2][0] - matrix.Matrix[2][0], Matrix[2][1] - matrix.Matrix[2][1], Matrix[2][2] - matrix.Matrix[2][2], Matrix[2][3] - matrix.Matrix[2][3],
                        Matrix[3][0] - matrix.Matrix[3][0], Matrix[3][1] - matrix.Matrix[3][1], Matrix[3][2] - matrix.Matrix[3][2], Matrix[3][3] - matrix.Matrix[3][3]);
    }

    Matrix4 Matrix4::operator/(Matrix4 matrix) {
        return Matrix4(Matrix[0][0] / matrix.Matrix[0][0], Matrix[0][1] / matrix.Matrix[0][1], Matrix[0][2] / matrix.Matrix[0][2], Matrix[0][3] / matrix.Matrix[0][3],
                        Matrix[1][0] / matrix.Matrix[1][0], Matrix[1][1] / matrix.Matrix[1][1], Matrix[1][2] / matrix.Matrix[1][2], Matrix[1][3] / matrix.Matrix[1][3],
                        Matrix[2][0] / matrix.Matrix[2][0], Matrix[2][1] / matrix.Matrix[2][1], Matrix[2][2] / matrix.Matrix[2][2], Matrix[2][3] / matrix.Matrix[2][3],
                        Matrix[3][0] / matrix.Matrix[3][0], Matrix[3][1] / matrix.Matrix[3][1], Matrix[3][2] / matrix.Matrix[3][2], Matrix[3][3] / matrix.Matrix[3][3]);
    }

    Matrix4 Matrix4::operator*(Matrix4 matrix) {
        Matrix4 mat;
        mat.Identity();
        for(int x = 0; x < 4; x++) {
            for(int y = 0; y < 4; y++) {
                float sum = 0;
                for(int i = 0; i < 4; i++) {
                    sum += matrix.Matrix[x][i] * matrix.Matrix[i][y];
                }
                mat.Matrix[x][y] = sum;
            }
        }
        return mat;
    }

    void Matrix4::SetOrtho(float left, float right, float bottom, float top, float m_near, float m_far) {
        float width = right - left;
        float height = top - bottom;
        float depth = m_far - m_near;

        Matrix[0][0] = 2.0f / width;
        Matrix[1][1] = 2.0f / height;
        Matrix[2][2] = 2.0f / depth;
        Matrix[3][0] = -(right + left) / width;
        Matrix[3][1] = -(top + bottom) / height;
        Matrix[3][2] = -(m_far + m_near) / depth;
    }

    void Matrix4::SetPerspective(float fov, float aspectRatio, float m_near, float m_far) {
        float q = 1.0f / Tan(deg2rad(0.5f * fov));
        float a = q / aspectRatio;

        float b = (m_near + m_far) / (m_near - m_far);
        float c = (2.0f * m_near * m_far) / (m_near - m_far);
        
        Matrix[0][0] = a;
        Matrix[1][1] = q;
        Matrix[2][2] = b;
        Matrix[2][3] = -1.0f;
        Matrix[3][2] = c;
    }

    static Matrix4 Matrix4::LookAt(const Vector3& camera, const Vector3& object, const Vector3& up) {
        Matrix4 output; output.Identity();
        Vector3 f = (object - camera).Normalized();
        Vector3 s = f.cross(up.Normalized());
        Vector3 u = s.cross(f);

        output.Matrix[0][0] = s.x;
        output.Matrix[1][0] = s.y;
        output.Matrix[2][0] = s.z;

        output.Matrix[0][1] = u.x;
        output.Matrix[1][1] = u.y;
        output.Matrix[2][1] = u.z;

        output.Matrix[0][2] = -f.x;
        output.Matrix[1][2] = -f.y;
        output.Matrix[2][2] = -f.z;

        Matrix4 translation; translation.SetTranslation(-camera.x, -camera.y, -camera.z);

        return result * translation;
    }

    static Matrix4 Matrix4::Invert(const Matrix4 matrix) { 
        float temp[16];

        // WIP
    }
}