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
#ifndef COMPLIST
#define COMPLIST

#include "ecstypes.hpp"

namespace fr::ecs {		
	class ICompList {
	public:
		ICompList() = default;
		virtual ~ICompList() = default;
		virtual void Erase(const EntityID entity) { }
		virtual void Insert(BaseComponent* component) { }
		const ComponentTypeID GetDataType() const { return typeID; }
	protected:
		ComponentTypeID typeID = INVALID_TYPE_ID;
	};

	template<typename T>
	class CompList : public ICompList {

	public:
		~CompList() = default;		
		CompList(): data({}) {
			typeID = CompType<T>();
		}

		void Insert(BaseComponent* component) override {
			T comp = *(static_cast<T*>(component));
			auto it = std::find_if(data.begin(), data.end(), [&comp](const T& c) { return c.GetID() == comp.GetID(); });
			assert(it == data.end() && "Trying to insert duplicate of component!");		
			data.push_back(comp);
		}

		T& Get(const EntityID entity) {
			auto it = std::find_if(data.begin(), data.end(), [&](const T& comp) { return comp.GetID() == entity; });
			assert(it != data.end() && "Trying to get non-existing component!");				
			return *it;
		}

		void Erase(const EntityID entity) override {
			auto it = std::find_if(data.begin(), data.end(), [&entity](const T& comp) { return comp.GetID() == entity; });
			if (it != data.end()) {
				data.erase(it);
			}
		}		

	private:	
		std::vector<T> data;		
	};
}

#endif