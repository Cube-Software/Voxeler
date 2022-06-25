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
#ifndef FR_MSEVENTS
#define FR_MSEVENTS

#include "event.hpp"

namespace fr::events{
    constexpr int MOUSE_LEFT = 0;
    constexpr int MOUSE_RIGHT = 1;
    constexpr int MOUSE_MIDDLE = 2;

    using MouseButton = int;
    using MouseButtonState = std::bitset<3>;

    struct MouseData : EventData {
        MouseButtonState buttons;
        double scrollX, scrollY = 0;
        double  lastX, lastY, posX, posY = 0;
    };

    // mouse events
    struct MouseEvent : public Event {
        virtual ~MouseEvent() = default;
        MouseEvent(const MouseData& d) : scrollX(d.scrollX), scrollY(d.scrollY),
            lastX(d.lastX), lastY(d.lastY), posX(d.posX), posY(d.posY) { }

        inline const EventID GetID() const { return EventTypeID<MouseEvent>(); }

        inline const double PosX() const { return posX; }
        inline const double PosY() const { return posY; }

        inline const double SrollX() const { return scrollX; }
        inline const double SrollY() const { return scrollY; }

        inline const double DeltaX() const { return (lastX - posX); }
        inline const double DeltaY() const { return (lastY - posY); }

    protected:
        double scrollX, scrollY;
        double  lastX, lastY, posX, posY;
    };

    // mouse down event
    struct MousePressEvent : public MouseEvent {
        ~MousePressEvent() = default;
        MousePressEvent(const MouseData& data) : MouseEvent(data) { }
        inline const EventID GetID() const { return EventTypeID<MousePressEvent>(); }
    };

    // moue up event
    struct MouseReleaseEvent : public MouseEvent {
        ~MouseReleaseEvent() = default;
        MouseReleaseEvent(const MouseData& data) : MouseEvent(data) { }
        inline const EventID GetID() const { return EventTypeID<MouseReleaseEvent>(); }
    };

    // motion event
    class MouseMotionEvent : public MouseEvent {
    public:
        ~MouseMotionEvent() = default;
        MouseMotionEvent(const MouseData& data) : MouseEvent(data) { }
        inline const EventID GetID() const { return EventTypeID<MouseMotionEvent>(); }
    };

    // scroll event
    class MouseScrollEvent : public MouseEvent {
    public:
        ~MouseScrollEvent() = default;
        MouseScrollEvent(const MouseData& data) : MouseEvent(data) { }
        inline const EventID GetID() const { return EventTypeID<MouseScrollEvent>(); }
    };
}

#endif