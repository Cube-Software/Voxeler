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

#include "memory.hpp"

namespace fr::core{
class string {
    private:
    char* data;
    size_t size;
    size_t capacity;

    public:
        string(const char* str) { string::operator=(str); }
        string(string&& other) { data = other.data; size = other.size; }
        string(const string& other) { string::operator=(other); }
        string(char c) { string::operator=(c); }

        void operator=(const char* str) {
            data = (char*)malloc(fr_strlen(str));
            fr_memcpy(data, str, fr_strlen(str) + 1);
            data[fr_strlen(str)] = '\0';
            size = fr_strlen(str);
        }
        void operator=(const string& other) {
            string::operator=(other.data);
        }
        void operator=(std::string other) {
            string::operator=(other.c_str());
        }

        void operator=(char c) {
            string::operator=(Makestring(c));
        }

        bool operator==(const char* str) {
            return fr_strcmp(data, str) == 0;
        }
        bool operator==(const string& str) {
            return fr_strcmp(data, str.data) == 0;
        }
        bool operator==(char c) {
            return fr_strcmp(data, Makestring(c)) == 0;
        }
        bool operator!=(const char* str) {
            return fr_strcmp(data, str);
        }

        bool operator!=(const string& str) {
            return fr_strcmp(data, str.data);
        }
        bool operator!=(char c) {
            return fr_strcmp(data, Makestring(c));
        }
        void Append(char c) {
            Append(Makestring(c));
        }
        void Append(const string& other) {
            Append(other.data);
        }

        size_t Size() const {
            return size;
        }
        const char* Cstring() const {
            return data;
        }
    };
}