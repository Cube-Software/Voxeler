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

#ifndef FR_WINDOW_HPP
#define FR_WINDOW_HPP

#include "../fr.hpp"
#include "../math/vectors.hpp"
#include "../core/deque.hpp"

#include <stdlib.h>

namespace fr::renderer {
	class frwindow;

	struct frPoint {
		int x, y;
	};

	// g means global
	static struct
	{
		core::frdeque<frwindow*> container;
	} g_WindowsManager;

	class frWindowsManager
	{
		public:
			static void PushWindow(frwindow* window);
			static frwindow* FindFromNativePointer(void* handle);
			static void EraseWindow(frwindow* wnd);

			static void PollEvents();
			static void Initialize();
	};

	class frwindow {
		public:
			frwindow() : _isRunning(true) { frWindowsManager::PushWindow(this); }
			~frwindow() { }

			virtual void Initialize(const char* title, const frPoint& dimension) = 0;
			virtual void* GetNativeHandle() const = 0;
			void Terminate() {
				_isRunning = false;
#if defined(FR_PLATFORM_WINDOWS)
				::PostQuitMessage(0);
#elif defined(FR_PLATFORM_LINUX)
				exit(0);
#endif
			}

			frPoint GetDimension() const { return _Dimension; }
			bool IsRunning() const { return _isRunning; }

			static frwindow* Create();
		protected:
			bool _isRunning;
			frPoint _Dimension;
	};
}

#endif