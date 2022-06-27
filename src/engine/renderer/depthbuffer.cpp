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

#include "depthbuffer.hpp"

namespace fr::renderer{
   depthbuffer::depthbuffer(GLsizei width, GLsizei height) {
           GLCALL(glGenTextures(1, &depthMapID));
           GLCALL(glBindTexture(GL_TEXTURE_2D, depthMapID));
           GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
           GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
           GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
           GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
           GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
           GLCALL(glGenFramebuffers(1, &bufferID));
           GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, bufferID));
           GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapID, 0));
           glDrawBuffer(GL_NONE);
           glReadBuffer(GL_NONE);
           assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "FAILED TO CREATE FBO");
           GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
           GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
   }
   depthbuffer::~depthbuffer() {
       GLCALL(glDeleteFramebuffers(1, &bufferID));
       GLCALL(glDeleteTextures(1, &depthMapID));
   }
   void depthbuffer::setsize(GLsizei width, GLsizei height) {
       GLCALL(glBindTexture(GL_TEXTURE_2D, depthMapID));
       GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL));
       GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
   }
   void depthbuffer::bind() {
       GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, bufferID));
   }
   void depthbuffer::unbind() {
       GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
   }
   void depthbuffer::clear() {
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, bufferID));
       GLCALL(glClear(GL_DEPTH_BUFFER_BIT));
   }
}  