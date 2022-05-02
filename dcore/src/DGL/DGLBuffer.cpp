#include "DGLBuffer.h"

namespace DGL
{
void DGLBuffer::Allocate(size_t size_b, BufFlag flag) {
    if (native_id == 0) return;
    glNamedBufferStorage(native_id, size_b, nullptr, static_cast<GLenum>(flag));
    buffer_size_b = size_b;
    allocated = true;
}
void DGLBuffer::Upload(size_t size_b, size_t offset_b, void* data) {
    if (native_id == 0) return;
    assert(size_b + offset_b <= buffer_size_b && "data size beyond allocated mem");
    glNamedBufferSubData(native_id, offset_b, size_b, data);
}
void DGLBuffer::Bind(BufType target) {
    if (native_id == 0) return;
    glBindBuffer(static_cast<GLenum>(target), native_id);
}

void DGLBuffer::Init() {
    glCreateBuffers(1, &native_id);
}
void DGLBuffer::OnRelease() {
    if (native_id) glDeleteBuffers(1, &native_id);
}

}
