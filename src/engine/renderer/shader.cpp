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
}