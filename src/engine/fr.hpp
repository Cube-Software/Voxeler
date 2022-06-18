#pragma once

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

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#if defined(_WIN32)
#include <windows.h>
#define DLLAPI __declspec(dllexport)
#elif defined(__linux__)
#include <bits/stdc++.h>
#define DLLAPI
#else
#warning Not Supported Platform!
#endif

#ifdef _WIN32
#define ASSERT(boolean) if (!(boolean)) __debugbreak();
#else
#define ASSERT(boolean) if (!(boolean)) raise(SIGTRAP);
#endif

#define GLCALL(func) GLClearError(); func; ASSERT(fr::GLLogCall(#func, __FILE__, __LINE__))

namespace fr {
    extern void GLClearError();
    extern bool GLLogCall(const char* function, const char* file, int line);
}

#endif