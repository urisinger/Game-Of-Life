#pragma once

class IndexBuffer
{
private:
	unsigned int BufferID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count, unsigned int index);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	inline unsigned int getcount() const { return m_Count; };
};