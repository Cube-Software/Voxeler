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
#ifndef COMPFACTORY
#define COMPFACTORY

#include "basecomp.hpp"

#include "../fr.hpp"

namespace fr::ecs {
    using Constructor = std::function<FactoryType()>;

    class ComponentFactory {

    public:
        ~ComponentFactory() = default;
        ComponentFactory(const ComponentFactory&) = delete;
        ComponentFactory& operator=(const ComponentFactory&) = delete;
        static ComponentFactory& Ref() {
            static ComponentFactory reference;
            return reference;
        }

        auto CreateComponent(const char* typeName) {            
            auto it = registryFuncs.find(typeName);
            assert(it != registryFuncs.end() && "Component Type not found in registry");
            auto component = it->second();
            return component;
        }

        void RegisterType(ComponentTypeID compType, const char* typeName, Constructor callback) {
            registryFuncs[typeName] = callback;
            registryTypes[typeName] = compType;
        }

        const ComponentTypeID GetTypeID(const char* typeName) {
            assert(registryTypes.find(typeName) != registryTypes.end() && "Typename out of range");
            return registryTypes.at(typeName);
        }

    private:
        ComponentFactory() = default;

    private:
        std::map<const char*, Constructor> registryFuncs;
        std::map<const char*, ComponentTypeID> registryTypes;
    };

    static ComponentFactory& CompFactory = ComponentFactory::Ref();

    template<typename T>
    class Registrar {
    public:
        Registrar(const char* typeName) {
            const ComponentTypeID compType = CompType<T>();
            CompFactory.RegisterType(compType, typeName, []()->FactoryType{ return std::move(std::make_shared<T>()); });
        }
    };

}

#endif