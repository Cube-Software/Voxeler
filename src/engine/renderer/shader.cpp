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

#include "shader.hpp"

namespace fr::renderer {
    void Shader::bind(){
        GLCALL(glUseProgram(program));
    }
    
    void Shader::unbind(){
        GLCALL(glUseProgram(0));
    }
    
    void Shader::setuniform(const GLchar* uName, GLint value){
        GLCALL(glUniform1i(glGetUniformLocation(program, uName), value));
    }
    
    void Shader::setuniform(const GLchar* uName, GLfloat value){
        GLCALL(glUniform1i(glGetUniformLocation(program, uName), value));
    }
    
    void Shader::setuniform(const GLchar* uName, GLfloat x, GLfloat y){
        GLCALL(glUniform2f(glGetUniformLocation(program, uName), x, y));
    }
    
    void Shader::setuniform(const GLchar* uName, GLfloat x, GLfloat y, GLfloat z){
        GLCALL(glUniform3f(glGetUniformLocation(program, uName), x, y, z));
    }    
    
    void Shader::setuniform(const GLchar* uName, math::Vector3 vector){
        GLCALL(glUniform3f(glGetUniformLocation(program, uName), vector.x, vector.y, vector.z));
    }
    
    void Shader::setuniform(const GLchar* uName, GLfloat x, GLfloat y, GLfloat z, GLfloat w){
        GLCALL(glUniform4f(glGetUniformLocation(program, uName), x, y, z, w));
    }
    
    void Shader::setuniform(const GLchar* uName, const GLfloat* mtx){
        GLCALL(glUniformMatrix4fv(glGetUniformLocation(program, uName), 1, GL_FALSE, mtx));
    }	
    
    void Shader::setuniform(const GLchar* uName, const math::Matrix4& mtx){
        GLCALL(glUniformMatrix4fv(glGetUniformLocation(program, uName), 1, GL_FALSE, mtx.ToPointer()));
    }
    
    void Shader::setuniform(const GLchar* uName, math::Vector2 vector){
        GLCALL(glUniform2f(glGetUniformLocation(program, uName), vector.x, vector.y));
    }
    
    void Shader::setuniform(const GLchar* uName, math::Vector4 vector){
        GLCALL(glUniform4f(glGetUniformLocation(program, uName), vector.x, vector.y, vector.z, vector.w));
    }
}