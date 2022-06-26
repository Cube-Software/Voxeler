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

#include "vertexarray.hpp"

namespace fr::renderer {
    vertexarray::vertexarray(const std::vector<vertex>& vertices, const std::vector<unsigned int>& indices) : vaoID(0), vboID(0), eboID(0) {
        create(vertices, indices);
    }

    vertexarray::~vertexarray() {
        destroy();
    }

    vertexarray::vertexarray(vertex* vertices, GLsizei vSize, GLuint* indices=nullptr, GLsizei iSize=0) : indicesCount(iSize), vertexCount(vSize) {
            glGenVertexArrays(1, &vaoID);
            glGenBuffers(1, &vboID);
            glGenBuffers(1, &eboID);
            
            glBindVertexArray(vaoID);
            glBindBuffer(GL_ARRAY_BUFFER, vboID);
            glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(vertex), vertices, GL_STATIC_DRAW);
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(GLuint), indices, GL_STATIC_DRAW);
            
            // Positions
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)0);
            // Normals
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, normal));
            // Texcoords
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (GLvoid*)offsetof(vertex, coords));

            glBindVertexArray(0);
            vertexCount /= sizeof(vertex);
    }

    void vertexarray::create(const std::vector<vertex>& vertices, const std::vector<unsigned int>& indices) {
        destroy();

        GLCALL(glGenVertexArrays(1, &vaoID));
        GLCALL(glBindVertexArray(vaoID));
        
        GLCALL(glGenBuffers(1, &vboID));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, vboID));
        GLCALL(glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex), &vertices[0], GL_STATIC_DRAW));

        GLCALL(glGenBuffers(1, &eboID));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID));
        GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW));

        GLCALL(glEnableVertexAttribArray(0));
        GLCALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0));
        GLCALL(glEnableVertexAttribArray(1));
        GLCALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(float) * 3)));
        GLCALL(glEnableVertexAttribArray(2));
        GLCALL(glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(float) * 6)));
        GLCALL(glEnableVertexAttribArray(3));
        GLCALL(glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(float) * 9)));

        GLCALL(glBindVertexArray(0));
        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }
    void vertexarray::destroy() const{
        if (vaoID != 0) {
            GLCALL(glDeleteVertexArrays(1, &vaoID));
            //vaoID = 0;
        }
        if (vboID != 0) {
            GLCALL(glDeleteBuffers(1, &vboID));
            //vboID = 0;
        }
        if (eboID != 0) {
            GLCALL(glDeleteBuffers(1, &eboID));
            //eboID = 0;
        }
    }

    void vertexarray::bind() const {
        GLCALL(glBindVertexArray(vaoID));
    }

    void vertexarray::unbind() const {
        GLCALL(glBindVertexArray(0));
    }

    void vertexarray::drawelements(GLenum mode = GL_TRIANGLES) const {
        GLCALL(glBindVertexArray(vaoID));
		GLCALL(glDrawElements(mode, indicesCount, GL_UNSIGNED_INT, 0));
		GLCALL(glBindVertexArray(0));
    }
        
    void vertexarray::drawarrays(GLenum mode = GL_TRIANGLES) const {
		GLCALL(glBindVertexArray(vaoID));
		GLCALL(glDrawArrays(mode, 0, vertexCount));
		GLCALL(glBindVertexArray(0));
    }

    void vertexarray::pushattribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLsizei offset) const {
        //GLCALL(glVertexAttribPointer(index, size, type, normalized, stride, offset));
        GLCALL(glEnableVertexAttribArray(index));
    }

    void vertexarray::pushattribute(GLuint index, GLint size, GLsizei stride, GLvoid* ptr) const {
		GLCALL(glEnableVertexAttribArray(index));
		 GLCALL(glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, size, ptr));
    }
}