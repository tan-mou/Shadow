#pragma once
#include<iostream>
#include"VertexShader.h"
#include"FragmentShader.h"
#include<GL/glew.h>
#include<string>
#include<sstream>
#include<fstream>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp> 
#include<glm/gtc/type_ptr.hpp>
class Shader
{
private:
	unsigned int id;
	std::stringstream vertexsource;
	std::stringstream fragmentsource;
public:
	
	Shader(const std::string& vertexfilepath, const std::string& fragmentfilepath);
	unsigned int Get_id() {
		return id;
	}
	void Use() {
		glUseProgram(id);

	}
	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(id, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(id, name.c_str()), value);
	}
	void setVec3(const std::string& name, glm::vec3 value) const
	{
		glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
	}
	void setVec4(const std::string& name, glm::vec4 value) const
	{
		glUniform4f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z,value.w);
	}
	void setMat4(const std::string& name, glm::mat4 value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
	}

	

};

