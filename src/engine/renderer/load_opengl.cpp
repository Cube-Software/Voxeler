#include "load_opengl.hpp"

#if defined(FR_PLATFORM_WINDOWS)
static HMODULE gl_lib = NULL;
#elif defined(FR_PLATFORM_LINUX)
static void* gl_lib = nullptr;
#include <dlfn.h>
#define GLX_GLXEXT_LEGACY
#include <GL/glx.h>
#endif

namespace fr::renderer {
    static void* load_opengl_function(const char* name) {
        void* res = nullptr;
#if defined(FR_PLATFORM_WINDOWS)
        res = GetProAddress(gl_lib, name);
#elif defined(FR_PLATFORM_LINUX)
        res = dlfcn(gl_lib, name);
#endif
        if(!res) {

        }

        return res;
    }

    bool InitializeOpenGL()
    {
#if defined(FR_PLATFORM_WINDOWS)
        gl_lib = LoadLibraryW(L"opengl32.dll");
#elif defined(FR_PLATFORM_LINUX)
        gl_lib = dlopen("libGL.so.1", RTLD_LOCAL | RTLD_LAZY);
        if(!gl_lib)
             gl_lib = dlopen("libGL.so", RTLD_LOCAL | RTLD_LAZY);
#endif

        if(!gl_lib)
            return false;

#define FR_GL_FN(tp, nm) nm = (tp)load_opengl_function(#nm);
#include "gl_load_helper.hpp"
#undef FR_GL_FN

#if defined(FR_PLATFORM_WINDOWS)
        FreeLibrary(gl_lib);
#elif defined(FR_PLATFORM_LINUX)
        dlclose(gl_lib);
#endif

        return true;
    }

}
