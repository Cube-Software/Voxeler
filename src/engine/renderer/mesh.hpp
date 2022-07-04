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

#ifndef FR_RENDERER_MESH_HPP
#define FR_RENDERER_MESH_HPP

#include "shader.hpp"
#include "vertex.hpp"
#include "vertexarray.hpp"
#include "material.hpp"

namespace fr::renderer
{
    class mesh {
    private:
        vertexarray m_vertexarray;
        material m_material;
    public:
        mesh(vertex* verticies, GLsizei vsize);
        mesh(vertex* verticies, GLsizei vsize, GLuint*, GLsizei isize);
        mesh(vertex* verticies, GLsizei vsize, GLuint*, GLsizei isize, const material& material);
        mesh(const vertexarray& vao) : m_vertexarray(vao) {}

        void render(Shader& shader);
        void draw_arrays(Shader& shader);
        void set_material(const material& _material);

        const material& get_material() const { return m_material; }
    };
    
}

#endif // FR_RENDERER_MESH_HPP
