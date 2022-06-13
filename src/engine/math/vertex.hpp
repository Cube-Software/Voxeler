#pragma once

#include "../math/vectors.hpp"

namespace fr::renderer {
    struct vertex {
        math::Vector3 position;
        math::Vector3 normal;
        math::Vector3 tangent;
        math::Vector3 bitangent;
        math::Vector2 coords;
    };
}