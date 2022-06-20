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

#ifndef FR_RENDERER_SHADER_HPP
#define FR_RENDERER_SHADER_HPP

#include "../fr.hpp"
#include "../math/vectors.hpp"

namespace fr::renderer {
    class Shader {
        public:
        Shader() : program(0) {}
        Shader(const GLuint id) : program(id) {}
        ~Shader() { glDeleteProgram(program); }

        void bind();
        void unbind();
        void setuniform(const GLchar* uName, GLint value);
        void setuniform(const GLchar* uName, GLfloat value);
        void setuniform(const GLchar* uName, GLfloat x, GLfloat y);
        void setuniform(const GLchar* uName, math::Vector2 vector);
        void setuniform(const GLchar* uName, GLfloat x, GLfloat y, GLfloat z);
        void setuniform(const GLchar* uName, math::Vector3 vector);
        void setuniform(const GLchar* uName, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
        void setuniform(const GLchar* uName, math::Vector4 vector);
        void setuniform(const GLchar* uName, const GLfloat* mtx);
        void setuniform(const GLchar* uName, const math::Matrix4& mtx);
        void setsample2d(const GLchar* uName, GLuint tex2d, GLint unit = 0);

        GLuint getuniform(const char* name);
        GLuint GetProgram() { return program; }
        
        int ID;

        private:
        void CheckErrors(GLuint shader, std::string type);
        GLuint program;
    };
}

#endif