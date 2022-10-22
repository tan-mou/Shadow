#pragma once
#include<iostream>
struct Shadertype {
	
};
class VertexShader
{
private:
	unsigned int vertexShader;

public:
	VertexShader(const char* source);


	unsigned int GetVertexShader();

};