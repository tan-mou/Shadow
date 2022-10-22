#include"Renderer.h"
void GLClearError() {
    while (glGetError() != GL_NO_ERROR);

}

bool GLLogCall(const char* function, const char* file, int line) {

    while (GLenum error = glGetError()) {//这个语句有点东西的，他会把错误都返回给error直到glgeterror返回gl_no_error
        std::cout << "[OpenGL_Error(" << error << ")]" << ":" << function << "\t" << "line:" << line << std::endl;
        return false;
    }
    return true;
}