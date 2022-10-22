#include "Shader.h"



Shader::Shader(const std::string& vertexfilepath, const std::string& fragmentfilepath) {
    std::ifstream stream1(vertexfilepath);

    std::string line;

    while (getline(stream1, line)) {
        vertexsource<< line << '\n';

    }
    std::ifstream stream2(fragmentfilepath);

    while (getline(stream2, line)) {
        fragmentsource << line << '\n';
    }




	VertexShader vShader(vertexsource.str().c_str());
	FragmentShader fShader(fragmentsource.str().c_str());
    int success;
    char infoLog[512];
    id = glCreateProgram();

    glAttachShader(id, vShader.GetVertexShader());
    glAttachShader(id, fShader.GetFragmentShader());
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glUseProgram(id);



    glValidateProgram(id);
    glDeleteShader(vShader.GetVertexShader());
    glDeleteShader(fShader.GetFragmentShader());

}