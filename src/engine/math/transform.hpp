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

// TRANSFORM COMPONENT

#ifndef FR_COMPONENTS_TRANSFORM_HPP
#define FR_COMPONENTS_TRANSFORM_HPP

#include "math.hpp"
#include "../ecs/basecomp.hpp"
#include "quaternion.hpp"
#include "matrix4.hpp"
#include "../renderer/shader.hpp"

namespace fr::components{
    struct transform : ecs::BaseComponent {
        transform() : position(0.0f), rotation(0.0f, 0.0f, 0.0f, 1.0f), scale(1.0f) {}
        ~transform() = default;

        transform(const math::Vector3& pos, const math::Quaternion& rot, const math::Vector3& sca) : position(pos), rotation(rot), scale(sca) {}
        transform(const math::Vector3& pos, const math::Quaternion& rot) : position(pos), rotation(rot) {}
        transform(const math::Vector3& pos) : position(pos) {}

        void operator=(const transform& t) {
            position = t.position;
            rotation = t.rotation;
            scale = t.scale;
        }

        math::Matrix4 getModelMatrix() const {
            math::Matrix4 modelMatrix = math::Matrix4();
            modelMatrix.SetTranslation(position.x, position.y, position.z);

            modelMatrix.SetRotationX(rotation.x);
            modelMatrix.SetRotationY(rotation.y);
            modelMatrix.SetRotationZ(rotation.z);

            modelMatrix.SetScale(scale.x,scale.y,scale.z);
            return modelMatrix;
        }

        void setModelUniform(renderer::Shader& shader) const {
            shader.bind();
            shader.setuniform("model", getModelMatrix());
        }

        math::Vector3 position;
        math::Quaternion rotation;
        math::Vector3 scale;
    };
    
}

#endif // FR_TRANSFORM_HPP