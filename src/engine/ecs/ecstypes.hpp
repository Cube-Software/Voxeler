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
#ifndef ECS_TYPES
#define ECS_TYPES

#include "../fr.hpp"

namespace fr::ecs {
	class Entity;
	class BaseSystem;
	class BaseComponent;
	class EntityManager;

	// global constantes
	constexpr int INVALID_TYPE_ID = 0;
	constexpr int INVALID_ENTITY = -1;
	constexpr int MAX_COMP_COUNT = 32;
	constexpr int MAX_ENTITY_COUNT = 5000;

	// typedefs
	using EntityID = int;
	using SystemTypeID = int;
	using ComponentTypeID = int;
	using Signature = std::set<ComponentTypeID>;
	using FactoryType = std::shared_ptr<BaseComponent>;
	using EntityList = std::vector<Entity>;
	using EntityIDList = std::vector<EntityID>;

	// Runtime type
	inline int GetRuntimeTypeID() {
		static int typeID = 1u;
		return typeID++;
	}

	template<typename T>
	inline SystemTypeID SystemType() noexcept {
		static_assert((std::is_base_of<BaseSystem, T>::value && !std::is_same<BaseSystem, T>::value), "Invalid template type");
		static const SystemTypeID typeID = GetRuntimeTypeID();
		return typeID;
	}

	template<typename T>
	inline ComponentTypeID CompType() noexcept {
		static_assert((std::is_base_of<BaseComponent, T>::value && !std::is_same<BaseComponent, T>::value), "Invalid template type");
		static const ComponentTypeID typeID = GetRuntimeTypeID();
		return typeID;
	}
}

#endif