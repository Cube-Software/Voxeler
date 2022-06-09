#pragma once

// make a OpenGL collor buffer class

#include "../fr.hpp"

namespace fr::renderer{
    class colorbuffer {
    public:
        colorbuffer() : bufferID(0), textureID(0) {}
        colorbuffer(GLsizei width, GLsizei height);
        ~colorbuffer();

        void setsize(GLsizei width, GLsizei height);
        void bind();
        void unbind();
        void clear();

        const GLuint TexID() const {
            return textureID;
        }

        const GLuint GetID() const {
            return textureID;
        }

    private:
        GLuint bufferID;
        GLuint textureID;
    };
}