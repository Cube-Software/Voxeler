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

#ifndef FR_RENDERER_VERTEXARRAY_HPP
#define FR_RENDERER_VERTEXARRAY_HPP

#include "../fr.hpp"
#include "vertex.hpp"

namespace fr::renderer {
    class vertexarray {
    private:
        GLuint vaoID;
        GLuint vboID;
        GLuint eboID;
        GLsizei vertexCount;
        GLsizei indicesCount;
        /*
        GLsizei stride;
        GLenum drawMode;
        GLenum indexType;
        GLenum indexOffset;
        GLenum indexDrawMode;
        GLenum indexDrawOffset;
        */
    public:
        vertexarray() : vaoID(0), vboID(0), eboID(0) { }
        vertexarray(const vertexarray&) = delete;
        vertexarray(vertexarray&&) = delete;
        vertexarray& operator=(const vertexarray&) = delete;
        vertexarray& operator=(vertexarray&&) = delete;

        vertexarray(const std::vector<vertex>& vertices, const std::vector<GLuint>& indices);
        vertexarray(const std::vector<vertex>& vertices);

        vertexarray(vertex* vertices, GLsizei vSize, GLuint* indices=nullptr, GLsizei iSize=0);
        ~vertexarray();

        void bind() const;
        void unbind() const;

        void drawelements(GLenum mode = GL_TRIANGLE_STRIP) const;
        void drawarrays(GLenum mode = GL_TRIANGLES) const;

        void pushattribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLsizei offset) const;
        void pushattribute(GLuint index, GLint size, GLsizei stride, GLvoid* ptr) const;

        void create(const std::vector<vertex>& vertices, const std::vector<unsigned int>& indices);
        void destroy() const;

        const GLuint GetVaoID() const { return vaoID; }
        const GLuint GetVboID() const { return vboID; }
        const GLuint GetEboID() const { return eboID; }
        const GLsizei GetVertexCount() const { return vertexCount; }
        const GLsizei GetIndicesCount() const { return indicesCount; }

    };
}

#endif // FR_RENDERER_VERTEXARRAY_HPP