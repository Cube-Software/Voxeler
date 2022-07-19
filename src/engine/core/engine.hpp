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
#ifndef FR_ENGINE_HPP
#define FR_ENGINE_HPP

#include "../ecs/entitymanager.hpp"
#include "../audio/AudioBijoux.hpp"
#include "timer.hpp"

namespace fr::engine
{

/* audio stuff */
static audio::AudioVoxelaux& Audio;

/* timer stuff */
static core::timer& Timer = core::timer::Ref();

/* ecs stuff */
static ecs::EntityManager& entityManager = ecs::EntityManager::Ref();

class Engine {
public:
    Engine();
    ~Engine();

    void Initialize();
    void Update();
    void Render();

    frwindow get_window() { return wnd; }
private:
    frwindow* wnd;
}

}

#endif