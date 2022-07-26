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

#include "context.hpp"

namespace fr::renderer {
#if defined(FR_PLATFORM_WINDOWS)
    class frContextImpl : public frcontext {
    public:
        frContextImpl() : _hDC(NULL) { }
        ~frContextImpl() { _hDC = NULL; }
        
        void SetCurrent(frwindow* curr) override { _hDC = GetDC((HWND)curr->GetNativeHandle()); }

        void MakeCurrent() override {
            
        }

        void ReleaseCurrent() override {

        }

        void SwapBuffers() override {
            ::SwapBuffers(_hDC);
        }

        void SetVsync(bool vsync) override {

        }

    private:
        HDC _hDC;
    };

#define CONTEXT_DEFINED
#elif defined(FR_PLATFORM_LINUX)
    class frContextImpl : public frcontext {
    public:
        frContextImpl() { }
        ~frContextImpl() { }
        
        void SetCurrent(frwindow* curr) override {  }

        void MakeCurrent() override {
            
        }

        void ReleaseCurrent() override {

        }

        void SwapBuffers() override {
            
        }

        void SetVsync(bool vsync) override {

        }
    };

#define CONTEXT_DEFINED
#endif

#ifndef CONTEXT_DEFINED
#error "Fractal doesn't support this platform!"
#endif
    // because platform window classes name is same
    frcontext* frcontext::Create() {
        new frContextImpl();
    }
}
