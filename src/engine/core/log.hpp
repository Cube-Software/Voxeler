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
#ifndef LOG
#define LOG

#include "../fr.hpp"
#include "../vendor/termcolor.hpp"

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

namespace fr::log {
		inline void ErrorLog(std::string log) { std::cout << termcolor::red << "[ERROR] " << log << termcolor::white << std::endl; }
		inline void WarnLog(std::string log) { std::cout << termcolor::bright_magenta << "[WARN] " << log << termcolor::white << std::endl; }
		inline void InfoLog(std::string log) {
		#ifndef FR_BUILD
			std::cout << "[" << termcolor::bright_green << " OK " << "] " << termcolor::white << log << std::endl; 
		#endif
		}
}

#define FR_INFO(...) fr::Log::InfoLog(__VA_ARGS__)
#define FR_ERROR(...) fr::Log::ErrorLog(__VA_ARGS__)
#define FR_WARNING(...) fr::Log::WarnLog(__VA_ARGS__)
#endif