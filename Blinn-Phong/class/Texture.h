#pragma once
#include<iostream>
#include<string>
#include<GL/glew.h>
#include"stb_image.h"
#define PNG 0
#define JPG 1
class Texture
{
private :
	unsigned int texture_id;
public:
	Texture(unsigned int texture_postion,std::string image_source,unsigned int type);
	void Bind();
	void UnBind();

};

