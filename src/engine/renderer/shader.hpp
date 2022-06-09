#pragma once

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
        void setuniform(const GLchar* uName, GLfloat x, GLfloat y, GLfloat z);
        void setuniform(const GLchar* uName, math::Vector3 vector);
        void setuniform(const GLchar* uName, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
        void setuniform(const GLchar* uName, const GLfloat* mtx);
        void setsample2d(const GLchar* uName, GLuint tex2d, GLint unit = 0);

        GLuint getuniform(const char* name);
        GLuint GetProgram() { return program; }
        
        int ID;

        private:
        void CheckErrors(GLuint shader, std::string type);
        GLuint program;
    };
}