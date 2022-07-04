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
#ifndef FR_RENDERER_MATERIAL_HPP
#define FR_RENDERER_MATERIAL_HPP

#include "shader.hpp"
#include "../math/vectors.hpp"

namespace fr::renderer
{
    class material
    {
    public:
        material() = default;
        material(math::Vector3 albedo, float metallic, float roughness, float Ambiento_oclussion) : Albedo(albedo), Metallic(metallic), Roughness(roughness), Ambient_Occlusion(Ambiento_oclussion) {}
        ~material() = default;

        GLfloat Shininess = 32.0f;
        GLfloat Ambient_Occlusion = 1.0f;
        GLfloat Opacity = 1.0f;
        GLfloat Metallic = 0.0f;
        GLfloat Roughness = 0.0f;
        GLfloat Reflectivity = 0.0f;
        math::Vector3 Diffuse = math::Vector3(0.5f, 0.5f, 0.5f);
        math::Vector3 Specular = math::Vector3(0.5f, 0.5f, 0.5f);
        math::Vector3 Ambient = math::Vector3(0.5f, 0.5f, 0.5f);
        math::Vector3 Albedo = math::Vector3(0.5f, 0.5f, 0.5f);
    
	    FRuint AoMap = 0;
	    FRuint NormalMap = 0;
	    FRuint AlbedoMap = 0;
	    FRuint MetallicMap = 0;
	    FRuint RoughnessMap = 0;
	    FRuint SpecularBRDFMap = 0;

        void setUniforms(Shader& shader);
    };
    
}

#endif // FR_RENDERER_MATERIAL_HPP
