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
#define CONTEXT_DEFINED
#endif

#ifndef CONTEXT_DEFINED
#error "Fractal doesn't support this platform!"
#endif
    // because platform window classes name is same
    frcontext* frcontext::Create() {
        return new frContextImpl();
    }
}
