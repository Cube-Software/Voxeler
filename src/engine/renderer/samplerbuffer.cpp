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

#include "samplerbuffer.hpp"

namespace fr::renderer 
{ 
	samplerbuffer::samplerbuffer(GLsizei w, GLsizei h) : width(w), height(h) {
		GLCALL(glGenTextures(1, &texID));
		GLCALL(glBindTexture(GL_TEXTURE_2D, texID));
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCALL(glBindTexture(GL_TEXTURE_2D, 0));

		GLCALL(glGenRenderbuffers(1, &renderID));
		GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, renderID));
		GLCALL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height));
		GLCALL(glBindRenderbuffer(GL_RENDERBUFFER, 0));

		GLCALL(glGenFramebuffers(1, &buffID));
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, buffID));
		
		GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texID, 0));
		GLCALL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderID));

		assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE && "FAILED TO CREATE FBO");
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}
	
	samplerbuffer::~samplerbuffer() {
		glDeleteTextures(1, &texID);
		glDeleteRenderbuffers(1, &renderID);
		glDeleteFramebuffers(1, &buffID);
	}

	void samplerbuffer::set_size(GLsizei w, GLsizei h) {
		width = w;
		height = h;
		GLCALL(glBindTexture(GL_TEXTURE_2D, texID));
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL));
		GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
	}

	void samplerbuffer::bind() { GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, buffID)); }
	void samplerbuffer::unbind() { GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0)); }

	void samplerbuffer::clear() {
		GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, buffID));
		GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
	}	

	void samplerbuffer::blit_to(GLuint targetbuffID) {
		GLCALL(glBindFramebuffer(GL_READ_FRAMEBUFFER, buffID));
		GLCALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, targetbuffID));
		glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
		GLCALL(glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0));
	}
		
}
