#include "FragmentShader.h"
#include<iostream>
#include<GL/glew.h>
FragmentShader::FragmentShader(const char* source) {
    int success;
    char infoLog[512];
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = source;

    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << source << std::endl;
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
unsigned int FragmentShader::GetFragmentShader() {

    return fragmentShader;
}