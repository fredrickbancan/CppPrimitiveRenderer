#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "VertexBuffer.h"
VertexBuffer::VertexBuffer(VertexBufferLayout& layout)
{
    /*creating a buffer int and telling opengl to use it to store the vertex data.*/
    glGenBuffers(1, &bufferInt);
    glBindBuffer(GL_ARRAY_BUFFER, bufferInt);
    this->layout = layout;
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &bufferInt);
}

void VertexBuffer::initDynamic(int initialByteSize)
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferInt);
    /*tells opengl to store the vertex data in the currently bound gl_array_buffer and how to do it.*/
    glBufferData(GL_ARRAY_BUFFER, initialByteSize, NULL, GL_DYNAMIC_DRAW);
}

void VertexBuffer::resizeBuffer(int newByteSize)
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferInt);
    /*tells opengl to store the vertex data in the currently bound gl_array_buffer and how to do it.*/
    glBufferData(GL_ARRAY_BUFFER, newByteSize, NULL, GL_DYNAMIC_DRAW);
}

void VertexBuffer::updateData(const void* data, int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferInt);
    /*tells opengl to store the vertex data in the currently bound gl_array_buffer and how to do it.*/
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void VertexBuffer::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, bufferInt);
}