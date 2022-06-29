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

#include "window.hpp"
#include "../core/string.hpp"

namespace fr::renderer {
    void frWindowsManager::PushWindow(frwindow* window) { g_WindowsManager.container.push_back(window); }
    frwindow* frWindowsManager::FindFromNativePointer(void* handle) {
        frwindow* res = nullptr;
        for (int i = 0; i < g_WindowsManager.container.size(); ++i) {
            if (g_WindowsManager.container[i]->GetNativeHandle() == handle) {
                res = g_WindowsManager.container[i];
                break;
            }
        }
        return res;
    }

    void frWindowsManager::EraseWindow(frwindow* wnd) {
        for (int i = 0; i < g_WindowsManager.container.size(); ++i) {
            if (g_WindowsManager.container[i] == wnd) {
                g_WindowsManager.container.erase(i);
                break;
            }
        }
    }

#if defined(FR_PLATFORM_WINDOWS)
    void frWindowsManager::PollEvents() {
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE) > 0) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }

    HINSTANCE s_Instance = NULL;
    const WCHAR* s_WindowClassName = L"FRwin32windowclass";

    class frWindowImpl : public frwindow {
    public:
        frWindowImpl() : _hWnd(NULL) { }
        ~frWindowImpl() {
            if (_hWnd) {
                DestroyWindow(_hWnd);
                _hWnd = NULL;
            }
        }

        LRESULT CALLBACK WndProc(UINT Msg, WPARAM wParam, LPARAM lParam) {
            switch (Msg)
            {
            case WM_QUIT:
                ::PostQuitMessage(0);
                break;
            case WM_CLOSE:
                _isRunning = false;
                break;
            }

            return ::DefWindowProcW(_hWnd, Msg, wParam, lParam);
        }

        void Initialize(const char* title, const frPoint& dimension) override {
            _Dimension = dimension;
            DWORD dwStyle = 0, dwExStyle = 0;
            dwExStyle |= WS_EX_APPWINDOW;
            dwStyle |= WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_MAXIMIZEBOX | WS_THICKFRAME;
            RECT rect = { 0, 0, (LONG)dimension.x, (LONG)dimension.y };
            AdjustWindowRectEx(&rect, dwStyle, FALSE, dwExStyle);
            WCHAR Buf[260];
            from_str(title, Buf);
            _hWnd = CreateWindowExW(dwExStyle, s_WindowClassName, Buf, dwStyle, CW_USEDEFAULT, CW_USEDEFAULT, dimension.x, dimension.y, NULL, NULL, s_Instance, NULL);
            ShowWindow(_hWnd, SW_SHOW);
            UpdateWindow(_hWnd);
        }

        void* GetNativeHandle() const override {
            return (void*)_hWnd;
        }

    private:
        HWND _hWnd;
    };

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
    {
        if (hWnd != NULL) {
            frWindowImpl* wnd = (frWindowImpl*)frWindowsManager::FindFromNativePointer(hWnd);
            if (wnd)
                return wnd->WndProc(Msg, wParam, lParam);
        }

        return ::DefWindowProcW(hWnd, Msg, wParam, lParam);
    }

    void frWindowsManager::Initialize() {
        s_Instance = GetModuleHandleW(nullptr);
        WNDCLASSEXW wndClass;
        wndClass.cbClsExtra = NULL;
        wndClass.cbSize = sizeof(WNDCLASSEX);
        wndClass.cbWndExtra = NULL;
        wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
        wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
        wndClass.hInstance = s_Instance;
        wndClass.lpszClassName = s_WindowClassName;
        wndClass.lpszMenuName = L"";
        wndClass.style = CS_HREDRAW | CS_VREDRAW;
        wndClass.lpfnWndProc = &WndProc;
        ASSERT(::RegisterClassExW(&wndClass) != 0);
    }

#define WINDOW_DEFINED
#elif defined(FR_PLATFORM_LINUX)

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xcms.h>
#include <X11/Xatom.h>
#include <X11/XKBlib.h>
#include <X11/Xresource.h>
#include <X11/extensions/Xinerama.h>
#include <X11/Xcursor/Xcursor.h>

#include <stdio.h>

Display* s_RootDisplay = nullptr;

Atom wmDeleteWindowAtom;
XIC ic;
XIM im;

void frWindowsManager::Initialize() 
{ 
    s_RootDisplay = XOpenDisplay(nullptr);
    wmDeleteWindowAtom = XInternAtom(s_RootDisplay, "WM_DELETE_WINDOW", False);
    im = XOpenIM(s_RootDisplay, nullptr, nullptr, nullptr);
}

class frWindowImpl : public frwindow {
    public:
    frWindowImpl() {}
    ~frWindowImpl() {}

    void Initialize(const char* title, const frPoint& dimension) override 
    {
        auto screen = XDefaultScreen(s_RootDisplay);
        auto rootWindow = XRootWindow(s_RootDisplay, screen);
        long visualMask = VisualScreenMask;
        int numberOfVisuals = 0;

        XVisualInfo vInfoTemplate;
        vInfoTemplate.screen = screen;
        XVisualInfo* visualInfo = XGetVisualInfo(s_RootDisplay, visualMask, &vInfoTemplate, &numberOfVisuals);
        Colormap colormap = XCreateColormap(s_RootDisplay, rootWindow, visualInfo->visual, AllocNone);
        XSetWindowAttributes windowAttributes;
	    windowAttributes.colormap = colormap;
	    windowAttributes.background_pixel = XBlackPixel(s_RootDisplay, screen);
	    windowAttributes.border_pixel = XBlackPixel(s_RootDisplay, screen);
	    windowAttributes.event_mask = KeyPressMask | KeyReleaseMask | StructureNotifyMask | ExposureMask;
        const Window wnd = XCreateWindow(s_RootDisplay, XRootWindow(s_RootDisplay, screen), 100, 100,
		    dimension.x, dimension.y, 0, visualInfo->depth, InputOutput,
		    visualInfo->visual,
		    CWBackPixel | CWBorderPixel | CWEventMask | CWColormap, &windowAttributes);
    
        _Handle = wnd;

        XMapWindow(s_RootDisplay, _Handle);
	    XStoreName(s_RootDisplay, _Handle, title);

	    ic = XCreateIC(im, XNInputStyle, 0 | XIMPreeditNothing | XIMStatusNothing, XNClientWindow, _Handle, NULL);

	    Atom protocols = wmDeleteWindowAtom;
	    XSetWMProtocols(s_RootDisplay, _Handle, &protocols, 1);
    }

    void* GetNativeHandle() const override { return (void*)_Handle; }

    private:
    Window _Handle;
};

 void frWindowsManager::PollEvents() 
{
    while(XPending(s_RootDisplay) > 0) {
        XEvent event;
		XNextEvent(s_RootDisplay, &event);
        
        if (XFilterEvent(&event, 0))
			continue;

        frWindowImpl* wnd = nullptr;
        switch (event.type)
		{
        case ClientMessage:
            if ((Atom)event.xclient.data.l[0] == wmDeleteWindowAtom)
            {
                wnd = (frWindowImpl*)FindFromNativePointer((void*)event.xclient.window);
                if(wnd != nullptr)wnd->Terminate();
            }
        
        break;

        case KeyPress:
            const KeySym key = XLookupKeysym(&event.xkey, 0);
            if (key == XK_Escape)
                printf("test\n");

        break;
        }
    }
}

#define WINDOW_DEFINED
#endif

#ifndef WINDOW_DEFINED
#error "Fractal doesn't support this platform!"
#endif
    // because platform window classes name is same
    frwindow* frwindow::Create() {
    return new frWindowImpl();
    }
}
