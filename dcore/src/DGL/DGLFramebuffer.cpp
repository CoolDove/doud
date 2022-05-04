#include "DGLFramebuffer.h"


namespace DGL
{

GLint DGLFramebuffer::CurrentFramebufferID(FramebufferType type) {
    GLenum t;
    switch (type) {
        case FramebufferType::FRAMEBUFFER: t = GL_FRAMEBUFFER_BINDING; break;
        case FramebufferType::DRAW_FRAMEBUFFER: t = GL_DRAW_FRAMEBUFFER_BINDING; break;
        case FramebufferType::READ_FRAMEBUFFER: t = GL_READ_FRAMEBUFFER_BINDING; break;
    }
    GLint get;
    glGetIntegerv(t, &get);
    return get;
}

void DGLFramebuffer::Init() {
    glCreateFramebuffers(1, &native_id);
}

void DGLFramebuffer::Bind(FramebufferType type) {
    if (native_id)
        glBindFramebuffer((GLenum)type, native_id);
}

void DGLFramebuffer::OnRelease() {
    if (native_id) glDeleteFramebuffers(1, &native_id);
}

void DGLFramebuffer::Attach(DGLTexture2D* tex, FramebufferAttachment attachment, int texlayer) {
    if (!native_id) return;
    if (tex && tex->GetNativeID()) {
        glNamedFramebufferTexture(native_id, (GLenum)attachment, tex->GetNativeID(), texlayer);
    }
}

void DGLFramebuffer::Dettach(FramebufferAttachment attachment) {
    if (native_id)
        glNamedFramebufferTexture(native_id, (GLenum)attachment, 0, 0);
}


}
