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
#pragma once

#include "../fr.hpp"
#include "glfwinput.hpp"
#include "eventsystem.hpp"

namespace fr::glfwinput {
	static MouseData& mouse = Events.MouseRef();
	static KeyBoard& keys = Events.KeyboardRef();

	void WindowCloseCallback(GLFWwindow* window) {
		Dispatcher.Post(WindowEvent());
		Dispatcher.Post(WindowCloseEvent());
	}

	void WindowResizedCallback(GLFWwindow* window, int width, int height) {
		Dispatcher.Post(WindowEvent());
		Dispatcher.Post(WindowResizedEvent(width, height));
	}

	void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
		switch (action) {
			case GLFW_PRESS: 
				keys.set(key);
				Dispatcher.Post(KeyPressedEvent()); 
				break;

			case GLFW_RELEASE:
				keys.reset(key);
				Dispatcher.Post(KeyReleasedEvent());  
				break;
		}

		Dispatcher.Post(KeyEvent());
	}

	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mod) {
		switch (action) {
			case GLFW_PRESS: 				
				Dispatcher.Post(MousePressEvent(mouse));				
				mouse.buttons.set(button);
				break;

			case GLFW_RELEASE: 
				Dispatcher.Post(MouseReleaseEvent(mouse));
				mouse.buttons.reset(button);
				break;
		}	

		Dispatcher.Post(MouseEvent(mouse));
	}

	void MouseMotionCallback(GLFWwindow* window, double x, double y) {
		mouse.lastX = mouse.posX;
		mouse.lastY = mouse.posY;
		mouse.posX = x;
		mouse.posY = y;
		Dispatcher.Post(MouseMotionEvent(mouse));
		Dispatcher.Post(MouseEvent(mouse));
	}

	void MouseScrollCallback(GLFWwindow* window, double x, double y) {
		mouse.scrollX = x;
		mouse.scrollY = y;
		Dispatcher.Post(MouseScrollEvent(mouse));
		Dispatcher.Post(MouseEvent(mouse));
	}
}