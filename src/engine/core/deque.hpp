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
#ifndef FR_VECTOR_HPP
#define FR_VECTOR_HPP

// deque class made by Yavuz

#include "memory.hpp"

#include <new>

namespace fr::core {
    template<typename T>
    class frdeque {
        public:
            frdeque() : _Ptr(nullptr), _Size(0), _Capacity(0) { }
            frdeque(frdeque&& rhs) { *this = rhs; }
            frdeque(const frdeque& rhs) { *this = rhs; }
            frdeque(FRuint size) { Resize(size); }
            ~frdeque() { _Ptr = nullptr; }

            frdeque& operator=(const frdeque& rhs) {
                Resize(rhs._Capacity);
                fr_memcpy(_Ptr, rhs._Ptr, rhs._Size);
                _Capacity = rhs._Capacity;
                _Size = rhs._Size;
                return *this;
            }

            frdeque& operator=(frdeque&& rhs) {
                _Ptr = rhs._Ptr;
                _Size = rhs._Size;
                _Capacity = rhs._Capacity;
            }

            T& operator[](FRuint index) {
                return _Ptr[index];
            }

            const T& operator[](FRuint index) const {
                return _Ptr[index];
            }

            void push_back(const T& item) {
                if (_Size == _Capacity)
                    ResizeGrow();

                new (_Ptr + _Size) T(item);
                ++_Size;
            }

            void push_back(T&& item) {
                if (_Size == _Capacity)
                    ResizeGrow();

                new (_Ptr + _Size) T(static_cast<T&&>(item));
                ++_Size;
            }

            void pop_back() {
                --_Size;
                _Ptr[_Size].~T();
            }

            void push_front(const T& item) {
                if (_Size == _Capacity)
                    ResizeGrow();
                
                ++_Size;
                for (int i = 0; i < _Size; ++i) {
                    new (_Ptr + i + 1) T(_Ptr[i]);
                    _Ptr[i].~T();
                }
                new (_Ptr + 0) T(item);
            }

            void push_front(T&& item) {
                if (_Size == _Capacity)
                    ResizeGrow();

                ++_Size;
                for (int i = 0; i < _Size; ++i) {
                    new (_Ptr + i + 1) T(_Ptr[i]);
                    _Ptr[i].~T();
                }
                new (_Ptr + 0) T(static_cast<T&&>(item));
            }

            void pop_front() {
                _Ptr[0].~T();
                for (int i = 0; i < _Size; ++i) {
                    new (_Ptr + i) T(_Ptr[i + 1]);
                    _Ptr[i + 1].~T();
                }

                --_Size;
            }

            void erase(FRuint index) {
                _Ptr[index].~T();
                for (int i = index; i < _Size; ++i) {
                    new (_Ptr + i) T(_Ptr[i + 1]);
                    _Ptr[i + 1].~T();
                }

                --_Size;
            }

            T& front() {
                return _Ptr[0];
            }

            const T& front() const {
                return _Ptr[0];
            }

            T& back() {
                return _Ptr[_Size - 1];
            }

            const T& back() const {
                return _Ptr[_Size - 1];
            }

            void Resize(FRuint size) {
                if (_Capacity != size) {
                    if (_Capacity == 0)
                        _Ptr = (T*)fr_alloc(size, 16);
                    else
                        _Ptr = (T*)fr_realloc(_Ptr, size, 16);

                    _Capacity = size;
                }
            }

            void ResizeGrow() {
                Resize(_Capacity == 0 ? 4 : _Capacity << 1);
            }

            const FRuint size() const {
                return _Size;
            }

            const FRuint capacity() const {
                return _Capacity;
            }

            T* data() {
                return _Ptr;
            }

            const T* data() const {
                return _Ptr;
            }
        private:
            T* _Ptr;
            FRuint _Size, _Capacity;
    };
}

#endif
