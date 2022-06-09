#include "window.hpp"

namespace fr::renderer {
	frwindow::frwindow(const char* title, math::Vector2 size) : Size(size) {
        if (!glfwInit())
            return;
        
        window = glfwCreateWindow(size.x, size.y, title, NULL, NULL);
        glfwMakeContextCurrent(window);
        if (!window) glfwTerminate();
        
        assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
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
