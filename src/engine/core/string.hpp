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
#ifndef FR_STRING_HPP
#define FR_STRING_HPP

// string class made by Yavuz
// very basic string class

#include "memory.hpp"
#include "deque.hpp"

inline int fr_strcmp(const char* s1, const char* s2) {
    const char* s_1 = s1;
    const char* s_2 = s2;
    while (*s_1 && *s_2) {
        ++s_1;
        ++s_2;
    }

    int cmp = *s_1 - *s_2;
    int abs_cmp = cmp < 0 ? -cmp : cmp;
    cmp /= cmp == 0 ? 1 : abs_cmp;
    return cmp;
}

inline size_t fr_strlen(const char* s) {
    size_t len = 0;
    do {
        ++len;
    } while (s[len]);
    return len;
}

inline void from_str(const char* src, wchar_t* dst) {
    while ((*(dst++) = (wchar_t)*(src++)) != 0);
    *dst = 0;
}

namespace fr::core{
class string {
    private:
    char* data;
    size_t size;

    public:
        string() : data(nullptr), size(0) { }
        string(const char* str) { string::operator=(str); }
        string(string&& other) { data = other.data; size = other.size; }
        string(const string& other) { string::operator=(other); }
        string(char c) { string::operator=(c); }

        char& operator[](size_t index) {
            return data[index];
        }

        const char& operator[](size_t index) const {
            return data[index];
        }

        void operator=(const char* str) {
            size_t sz = fr_strlen(str);
            data = (char*)fr_alloc(sz + 1, 16);
            fr_memcpy(data, str, sz);
            data[sz] = 0;
            size = sz;
        }
        void operator=(const string& other) {
            string::operator=(other.data);
        }
        void operator=(string&& rhs) {
            data = rhs.data;
            size = rhs.size;
        }

        void operator=(char c) {
            string::operator=(&c);
        }

        bool operator==(const char* str) {
            return fr_strcmp(data, str) == 0;
        }
        bool operator==(const string& str) {
            return fr_strcmp(data, str.data) == 0;
        }
        bool operator==(char c) {
            return fr_strcmp(data, &c) == 0;
        }
        bool operator!=(const char* str) {
            return fr_strcmp(data, str) != 0;
        }

        bool operator!=(const string& str) {
            return fr_strcmp(data, str.data) != 0;
        }
        bool operator!=(char c) {
            return fr_strcmp(data, &c) != 0;
        }
        void operator+=(const char* str) {
            Append(str);

        }

        void operator+=(char value) {
            Append(value);
        }

        void operator+=(const string& rhs) {
            Append(rhs);
        }
        void Append(const char* str) {
            size_t sz = fr_strlen(str);
            const size_t tmp = size;
            Resize(sz + tmp);
            fr_memcpy(data + tmp, str, sz);
            
        }
        void Append(char c) {
            Append(&c);
        }
        void Append(const string& other) {
            Append(other.data);
        }

        void Resize(size_t _size) {
            if (size != _size) {
                if (size == 0)
                    data = (char*)fr_alloc(_size + 1, 16);
                else
                    data = (char*)fr_realloc(data, _size + 1, 16);

                size = _size;
            }

            data[_size = 0];
        }

        size_t Size() const {
            return size;
        }

        char* Data() {
            return data;
        }

        const char* c_str() const {
            return data;
        }

        void PopBack() {
            if (size > 0) {
                size--;
                data[size] = 0;
            }
        }

        void Clear() {
            size = 0;
            if (data != nullptr)
                data[size] = 0;
        }
    };

    inline string parsestring(const string& src, size_t size, size_t start)
    {
        string res;
        res.Resize(size);
        char* dst = res.Data();
        fr_memcpy(dst, src.c_str() + start, size);
    }

    inline frdeque<string> frsplitstring(const string& src, const string& tok)
    {
        frdeque<string> toks;
        int pos = 0;
        int lst = 0;
        while (src[pos]) 
        {
            if (parsestring(src, tok.Size(), (size_t)pos) == tok)
            {
                toks.push_back(parsestring(src, pos, pos - lst));
                lst = pos;
            }

            ++pos;
        }

        return toks;
    }
}

#endif

