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

#include "file_stream.hpp"

namespace fr::core {

    void file_stream::close_file()
    {
        if (_handle)
        {
#if defined(FR_PLATFORM_WINDOWS)
            CloseHandle(_handle);
#elif defined(FR_PLATFORM_LINUX)
#endif

            _handle = nullptr;
        }
    }

    void file_stream::open_handle_writable()
    {
#if defined(FR_PLATFORM_WINDOWS)
        _handle = ::CreateFileA(_load_path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
#elif defined(FR_PLATFORM_LINUX)
#endif
    }

    void file_stream::open_handle_readable()
    {
#if defined(FR_PLATFORM_WINDOWS)
        _handle = ::CreateFileA(_load_path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
#elif defined(FR_PLATFORM_LINUX)
#endif
    }

    void file_stream::write_buffer(const void* buf, size_t bytes)
    {
        size_t written = 0;
#if defined(FR_PLATFORM_WINDOWS)
        ::WriteFile(_handle, buf, (DWORD)bytes, (DWORD*)&written, nullptr);
#elif defined(FR_PLATFORM_LINUX)
#endif
    }

    void file_stream::read_buffer(void* buf, size_t size)
    {
        size_t readed = 0;
#if defined(FR_PLATFORM_WINDOWS)
        ::ReadFile(_handle, buf, (DWORD)size, (DWORD*)&readed, nullptr);
#elif defined(FR_PLATFORM_LINUX)
#endif
    }

    size_t file_stream::get_size() const
    {
#if defined(FR_PLATFORM_WINDOWS)
        return (size_t)::GetFileSize(_handle, 0);
#elif defined(FR_PLATFORM_LINUX)
#endif
    }

    size_t file_stream::get_pos()
    {
#if defined(FR_PLATFORM_WINDOWS)
        return (size_t)::SetFilePointer(_handle, 0, nullptr, FILE_CURRENT);
#elif defined(FR_PLATFORM_LINUX)
#endif
    }

    void file_stream::flushf()
    {
#if defined(FR_PLATFORM_WINDOWS)
        FlushFileBuffers(_handle);
#elif defined(FR_PLATFORM_LINUX)
#endif
    }

    bool file_stream::seekf(size_t pos)
    {
#if defined(FR_PLATFORM_WINDOWS)
        LARGE_INTEGER dist;
        dist.QuadPart = pos;
        return ::SetFilePointer(_handle, dist.u.LowPart, &dist.u.HighPart, FILE_BEGIN) != INVALID_SET_FILE_POINTER;
#elif defined(FR_PLATFORM_LINUX)
#endif
    }

}
