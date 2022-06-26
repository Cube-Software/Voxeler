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

#include "window.hpp"

namespace fr::renderer {
	frwindow::frwindow(const char* title, math::Vector2 size) : Size(size) {
        if (!glfwInit())
            return;
        
        window = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
        glfwMakeContextCurrent(window);
        if (!window) glfwTerminate();
        
        #if defined(FR_GLEW)
        GLenum err = glewInit();
		if (GLEW_OK != err) { fprintf(stderr, "Error: %s\n", glewGetErrorString(err)); }
        #elif defined(FR_GLAD)
        assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
        #endif

        glViewport(0, 0, size.x, size.y);
        while (glfwWindowShouldClose(window) == 0) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glfwTerminate();
        return;
	}
}
