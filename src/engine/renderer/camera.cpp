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

#include "camera.hpp"

namespace fr::components {
    void Camera::set_uniform_vp(renderer::Shader shader, math::Vector2 display_size, float factor = 1.0f) {
        shader.bind();
        shader.setuniform("Projection", get_projection(display_size));
        shader.setuniform("View", get_view(factor));
    }

    const math::Vector3 Camera::cast_ray(math::Vector2 display_size, math::Vector2 pos) {
        math::Vector2 mouse_ndc = math::Vector2(((pos.x * 2.0f) / display_size.x) - 1.0f, ((pos.y * 2.0f) / display_size.y) - 1.0f);
        mouse_ndc.y = -mouse_ndc.y;
        math::Vector4 ray_clip = math::Vector4(mouse_ndc.x, mouse_ndc.y, -1.0f, 1.0f);
        //math::Vector4 ray_eye = math::Matrix4::inverse(get_projection()) * ray_clip;

    }

    math::Matrix4 Camera::get_view(float factor) {
        math::Matrix4 view = math::Matrix4();
        view.Identity();
        view.SetTranslation(position.x * factor, position.y * factor, position.z * factor);
        view.SetRotationX(rotation.x);
        view.SetRotationY(rotation.y);
        view.SetRotationZ(rotation.z);
        return view;
    }

    math::Matrix4 Camera::get_projection(math::Vector2 size) {
        math::Matrix4 projection = math::Matrix4();
        projection.Identity();
        projection.SetPerspective(fov, size.x / size.y, near, far);
        return projection;
    }
}