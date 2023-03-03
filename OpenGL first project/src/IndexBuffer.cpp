#include "indexbuffer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count,unsigned int index)
    : m_Count(count)
{
    glGenBuffers(index, &BufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}


IndexBuffer :: ~IndexBuffer()
{
    glDeleteBuffers(1, &BufferID);
}

void IndexBuffer :: adddata(const unsigned int* data, unsigned int count, unsigned int index) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}


void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
}

void IndexBuffer::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}