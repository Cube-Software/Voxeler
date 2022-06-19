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
#ifndef BASESYSTEM
#define BASESYSTEM

#include "ecstypes.hpp"

namespace fr::ecs {
	class BaseSystem {
	public:
		BaseSystem() = default;
		virtual ~BaseSystem() = default;

		inline const Signature GetSignature() const { return signature; }

		inline void EraseEntity(const EntityID entity) { entities.erase(entity); }
		inline void PushEntity(const EntityID entity) { entities.insert(entity); }

		template<typename T>
		inline void AddComponentSignature() { signature.insert(CompType<T>()); }	

		inline const bool IsEmpty() const { return (entities.size() == 0);}
		inline const bool HasEntity(EntityID entity) const { return (entities.count(entity) > 0);}

		virtual void Stop() {}
		virtual void Start() {}
		virtual void Render() {}
		virtual void Update() {}
		virtual void Awake() {}

	protected:
		Signature signature;
		std::set<EntityID> entities;
	};
}
#endif