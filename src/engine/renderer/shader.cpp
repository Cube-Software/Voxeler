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

    void Shader::load(std::string vsh, std::string fsh){
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
            unsigned int vertex, fragment;
            int success;
            char infoLog[512];

            vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
            try {
                vShaderFile.open(vsh);
                fShaderFile.open(fsh);
                std::stringstream vShaderStream, fShaderStream;
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();	
                vShaderFile.close();
                fShaderFile.close();
                vertexCode   = vShaderStream.str();
                fragmentCode = fShaderStream.str();	
            }
            catch(std::ifstream::failure e){ std::cout << "SHADER FILE NOT SUCCESFULLY READ" << std::endl; }
            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();
                        
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);
            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
            if(!success) {
                glGetShaderInfoLog(vertex, 512, NULL, infoLog);
                std::cout << "SHADER VERTEX COMPILATION FAILED\n" << infoLog << std::endl;
            };
            program = glCreateProgram();
            glAttachShader(program, vertex);
            glAttachShader(program, fragment);
            glLinkProgram(program);
            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(program, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINKING FAILED\n" << infoLog << std::endl;
            }
            glDeleteShader(vertex);
            glDeleteShader(fragment);
    }
}