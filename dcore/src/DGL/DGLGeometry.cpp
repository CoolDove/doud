#include "DGLGeometry.h"

namespace DGL
{

void DGLVertexAttributeSet::Init(std::initializer_list<Attribute> attribs) {
    glCreateVertexArrays(1, &native_id);
    int i = 0;
    int offset = 0; // byte offset
    for (auto ite = attribs.begin(); ite != attribs.end(); ite++) {
        glVertexArrayAttribFormat(native_id, i, ite->dimension, GL_FLOAT, false, offset);
        glVertexArrayAttribBinding(native_id, i, 0);
        glEnableVertexArrayAttrib(native_id, i);

        offset += sizeof(float) * ite->dimension;
        i++;
        attributes.push_back(*ite);
    }
    total_size_b = offset;
}
void DGLVertexAttributeSet::AttachVertexBuffer(DGLBuffer* vbuf) {
    if (native_id) glVertexArrayVertexBuffer(native_id, 0, vbuf->GetNativeID(), 0, total_size_b);
}
void DGLVertexAttributeSet::AttachIndexBuffer(DGLBuffer* ibuf) {
    if (native_id) glVertexArrayElementBuffer(native_id, ibuf->GetNativeID());
}
void DGLVertexAttributeSet::Bind() {
    if (native_id) glBindVertexArray(native_id);
}
void DGLVertexAttributeSet::OnRelease() {
    if (native_id) glDeleteVertexArrays(1, &native_id);
}

}
