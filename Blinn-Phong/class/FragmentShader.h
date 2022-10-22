#pragma once
class FragmentShader
{
private: unsigned int fragmentShader;

public:
	FragmentShader(const char* source);
	unsigned int GetFragmentShader();

};

