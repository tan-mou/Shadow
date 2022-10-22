#pragma once
class VertexBuffer
{
private:
	unsigned int Ibo_ID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();


	void Bind();
	void UnBind();
};