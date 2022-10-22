#include"VertexBuffer.h"

#include"Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {

    GLCall(glGenBuffers(1, &Ibo_ID));
    glBindBuffer(GL_ARRAY_BUFFER, Ibo_ID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &Ibo_ID);
}


void VertexBuffer::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, Ibo_ID);
}
void VertexBuffer::UnBind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}