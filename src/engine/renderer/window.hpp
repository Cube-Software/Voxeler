#pragma once

#include "../fr.hpp"

namespace fr::renderer {
	class frwindow {
		public:
			frwindow(const char* title, math::Vector2 size);
			frwindow() { frwindow("fractal", math::Vector2(1024, 940)); }
			GLFWwindow* GetGLFWWindow() { return window; }

			void SetVsync(int interval) { glfwSwapInterval(interval); }

			math::Vector2 GetSize() { return Size; }
		private:
			math::Vector2 Size;
			GLFWwindow* window;
	};
}