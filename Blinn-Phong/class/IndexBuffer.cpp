#include"IndexBuffer.h"

#include"Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int * data, unsigned int count) {

    GLCall(glGenBuffers(1, &Ibo_ID));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ibo_ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
    m_Count = count;
}
IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &Ibo_ID);
}


void IndexBuffer::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Ibo_ID);
}
void IndexBuffer::UnBind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}