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

#include "colorbuffer.hpp"

namespace fr::renderer{
    colorbuffer::colorbuffer(GLsizei width, GLsizei height) {
        GLCALL(glGenFramebuffers(1, &bufferID));
        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, bufferID));
        GLCALL(glGenTextures(1, &textureID));
        GLCALL(glBindTexture(GL_TEXTURE_2D, textureID));
        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0));
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "FAILED TO CREATE AN FBO!!" << std::endl;
        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }
    colorbuffer::~colorbuffer() {
        glDeleteFramebuffers(1, &bufferID);
        glDeleteTextures(1, &textureID);
    }
    void colorbuffer::setsize(GLsizei width, GLsizei height) {
        GLCALL(glBindTexture(GL_TEXTURE_2D, textureID));
        GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
    }
    void colorbuffer::bind() {
        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, bufferID));
    }
    void colorbuffer::unbind() {
        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
    }
    void colorbuffer::clear() {		
        GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, bufferID));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT));
    }
}