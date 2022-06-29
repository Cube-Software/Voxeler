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
#ifndef FR_MEMORY_HPP
#define FR_MEMORY_HPP

// memory functions made by Yavuz

#include "../fr.hpp"

#include <malloc.h>
#include <stdlib.h>

namespace fr {
	inline void* fr_memcpy(void* dst, const void* src, size_t size) {
		FRuchar* byteDst = (FRuchar*)dst;
		const FRuchar* byteSrc = (const FRuchar*)src;
		size_t count = size;
		if (byteDst == nullptr || byteSrc == nullptr)
			return nullptr;
		while (count > 0)
		{
			*(byteDst++) = *(byteSrc++);
			--count;
		}
		return dst;
	}

	inline bool fr_memcmp(const void* f, const void* s, size_t size) {
		const FRuchar* bytef = (const FRuchar*)f;
		const FRuchar* bytes = (const FRuchar*)s;
		size_t count = size;
		if (bytef == nullptr || bytes == nullptr)
			return false;
		while (count > 0)
		{
			if (*(bytef++) == *(bytes++))
			{
				return true;
				break;
			}
			--count;
		}
		return false;
	}

	void fr_free(void* block);

	inline void* fr_alloc(size_t size, size_t alignment) {
#if defined(FR_PLATFORM_WINDOWS)
		return _aligned_malloc(size, alignment);
#elif defined(FR_PLATFORM_LINUX)
		void* mem = nullptr;
		posix_memalign(&mem, alignment, size);
		return mem;
#endif
	}

	inline void* fr_realloc(void* block, size_t size, size_t alignment) {
#if defined(FR_PLATFORM_WINDOWS)
		return _aligned_realloc(block, size, alignment);
#elif defined(FR_PLATFORM_LINUX)
		void* mem = fr_alloc(size, alignment); 
		fr_memcpy(mem, block, size); 
		fr_free(block); 
		return mem;
#endif
	}

	inline void fr_free(void* block) {
#if defined(FR_PLATFORM_WINDOWS)
		_aligned_free(block);
#elif defined(FR_PLATFORM_LINUX)
		free(block);
#endif
	}
}

#endif