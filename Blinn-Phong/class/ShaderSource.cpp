#include "ShaderSource.h"
ShaderSource::ShaderSource(const std::string& filepath) {
        std::ifstream stream(filepath);

        std::string line;
   
        while (getline(stream, line)) {
            ss << line << '\n';

        }

}
const char *ShaderSource::GetSource(){

    return ss.str().c_str();
}
