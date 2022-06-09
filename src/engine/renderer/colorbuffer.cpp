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
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
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