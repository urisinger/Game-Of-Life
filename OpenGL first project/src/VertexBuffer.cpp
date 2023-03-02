#include "vertexbuffer.h"

#include "DrawBoard.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) 
{
    glGenBuffers(1, &BufferID);
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}


VertexBuffer :: ~VertexBuffer()
{
    glDeleteBuffers(1, &BufferID);
}

void VertexBuffer::AddData(const void* data, unsigned int size)
{
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, BufferID);
}

void VertexBuffer::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
