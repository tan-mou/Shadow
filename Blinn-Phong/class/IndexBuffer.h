#pragma once
class IndexBuffer
{
private:
	unsigned int Ibo_ID;
	unsigned int m_Count;
public:
	IndexBuffer(const unsigned int * data, unsigned int count);
	~IndexBuffer();


	void Bind();
	void UnBind();
};