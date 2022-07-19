/*
    Voxeler - open source blockchain-based Roblox-like 3D game
    Based on Fractal Engine
    Created by CubeSoftware

    -------------------------------
    Copyright (c) 2021-2022 CubeSoftware
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef VOXELER_CAMMOV_HPP
#define VOXELER_CAMMOV_HPP

#include "../engine/math/transform.hpp"
#include "../engine/ecs/basecomp.hpp"
#include "../engine/ecs/basesystem.hpp"
#include "../engine/renderer/camera.hpp"
#include "../engine/renderer/shader.hpp"

class cameraMovementSystem : public fr::ecs::basesystem {
private:
    fr::components::camera m_camera;
    fr::renderer::Shader skybox;
    fr::renderer::Shader shaders[3];
public:
    cameraMovementSystem() {}

    void set_shaders_uniforms() {}
}

#endif //VOXELER_CAMMOV_HPP