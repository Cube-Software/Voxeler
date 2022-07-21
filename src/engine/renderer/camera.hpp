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

#ifndef FR_COMPNENTS_CAMERA_HPP
#define FR_COMPNENTS_CAMERA_HPP

#include "../core/engine.hpp"
#include "shader.hpp"
#include "../ecs/basecomp.hpp"
#include "../math/math.hpp"

namespace fr::components {
    struct Camera : public ecs::BaseComponent {
        Camera() = default;
        ~Camera() = default;
        
        Camera(float _fov, float _near, float _far) : fov(_fov), near(_near), far(_far) {}
        Camera(float _fov, float _near, float _far, math::Vector3 pos, math::Vector3 rot) : fov(_fov), near(_near), far(_far), position(pos), rotation(rot) {}

        void set_uniform_vp(renderer::Shader shader, math::Vector2 display_size, float factor);
        const math::Vector3 cast_ray(math::Vector2 display_size, math::Vector2 pos);

        math::Matrix4 get_view(float factor = 1.0f);
        math::Matrix4 get_projection(math::Vector2 size);

        float fov = 45.0f;
        float near = 0.1f;
        float far = 1000.0f;

        math::Vector3 position;
        math::Vector3 rotation;
    };

    class CameraSystem : public ecs::BaseSystem{
    private:
        renderer::Shader skybox;
        renderer::Shader shaders[1];

    public:
        CameraSystem();

        void Update(){
            for (auto entity : entities) {
                /*
                auto& camera = engine::entityManager.GetComponent<Camera>(entity);
                auto& transform = engine::entityManager.GetComponent<transform>(entity);

                camera.position = transform.position;

                camera.rotation.x = transform.rotation.x;
                camera.rotation.y = transform.rotation.y;
                camera.rotation.z = transform.rotation.z;
                */
            }
        }

    };
}

#endif // FR_COMPNENTS_CAMERA_HPP
