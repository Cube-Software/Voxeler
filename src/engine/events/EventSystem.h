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
#pragma once

#include "AppEvents.h"
#include "KeyEvents.h"
#include "MouseEvents.h"
#include "WindowEvents.h"
#include "Dispatcher.h"

class EventSystem {
public:
    EventSystem& operator=(const EventSystem&) = delete;
    EventSystem(const EventSystem&) = delete;
    ~EventSystem() = default;

    static EventSystem& Ref() {
        static EventSystem ref;
        return ref;
    }

    inline void Poll() { glfwPollEvents(); }

    inline KeyBoard& KeyboardRef() { return keys; }
    inline MouseData& MouseRef() { return mouse; }

    inline const bool IsKeyPressed(KeyCode key) const { return keys.test(key); }
    inline const bool IsMouseDown(MouseButton button) const { return mouse.buttons.test(button); }

private:
    EventSystem() = default;

private:
    KeyBoard keys;  
    MouseData mouse;
};

static EventSystem& Events = EventSystem::Ref();