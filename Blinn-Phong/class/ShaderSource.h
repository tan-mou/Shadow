#pragma once
#include<iostream>
#include<sstream>
#include<fstream>
#include<string.h>
class ShaderSource
{
private:const char* shadersource;
std::stringstream ss;
public:
    ShaderSource(const std::string& filepath);
    const char* GetSource();

};

