#pragma once

#include "basic_functions.hpp"
#include "quaternion.hpp"
#include "vectors.hpp"
#include "../scene/component.hpp"

namespace fr::components {
    class Transform : public fr::ecs::component {
        public:
        Transform();
        ~Transform();

        math::Vector3 position;
        math::Vector3 scale;
        math::Quaternion rotation;

        void Normalize();
    };
}