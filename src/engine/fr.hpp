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

#ifndef FR_HPP
#define FR_HPP

#include <set>
#include <map>
#include <array>
#include <tuple>
#include <queue>
#include <vector>
#include <string>
#include <bitset>
#include <stdio.h>
#include <memory>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <unordered_map>
#include <stdlib.h>

#if defined(_WIN32)
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#define DLLAPI __declspec(dllexport)
#define FR_PLATFORM_WINDOWS
#define FR_GLAD
#elif defined(__linux__)
#include <bits/stdc++.h>
#define FR_GLEW
#define DLLAPI
#define FR_PLATFORM_LINUX
#else
#warning Not Supported Platform!
#endif

#if defined(FR_GLEW)
/* glew */
#include <GL/glew.h>
#elif defined(FR_GLAD)
/*glad */
#include <glad/glad.h>
#endif
/* openal-soft */
#include <AL/al.h>
#include <AL/alc.h>
/* libsndfile */
#include <sndfile.h>
/* tiny xml */
#include <tinyxml2.h>

namespace fr {	
    extern void GLClearError();
	extern bool GLLogCall(const char* function, const char* file, int line);
}

#ifdef _WIN32
#define ASSERT(boolean) if (!(boolean)) __debugbreak();
#else
#define ASSERT(boolean) if (!(boolean)) raise(SIGTRAP);
#endif

#define GLCALL(func) GLClearError(); func; ASSERT(fr::GLLogCall(#func, __FILE__, __LINE__))

namespace fr {
	using FRuint = uint32_t;
	using FRuint64 = unsigned long long;
	using FRuchar = unsigned char;
	using FRboolean = bool;
	using FRchar = char;
	using FRint = int;
	using FRfloat = float;
	using FRlong = long;
	using FRvoid = void;
	typedef void(*func)();
	struct CommandLineArgs { int argc; char** args; };
}
#endif
