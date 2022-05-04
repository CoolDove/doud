#pragma once
#include <glad/glad.h>
#include <stdint.h>
#include "DGLEnum.h"
#include "DGLObject.h"
#include "DGLTexture.h"
#include <memory>


namespace DGL
{
enum class FramebufferType : uint32_t
{
    DRAW_FRAMEBUFFER = 0x8CA9,
    FRAMEBUFFER      = 0x8D40,
    READ_FRAMEBUFFER = 0x8CA8,
};

enum class FramebufferAttachment : uint32_t
{
    DEPTH = 0x8D00,
    STENCIL = 0x8D20,
    DEPTH_STENCIL = 0x821A,
    COLOR0 = 0x8CE0,
    COLOR1 = 0x8CE1,
    COLOR2 = 0x8CE2,
    COLOR3 = 0x8CE3,
    COLOR4 = 0x8CE4,
    COLOR5 = 0x8CE5,
    COLOR6 = 0x8CE6,
    COLOR7 = 0x8CE7,
    COLOR8 = 0x8CE8,
    COLOR9 = 0x8CE9,
    COLOR10 = 0x8CEA,
    COLOR11 = 0x8CEB,
    COLOR12 = 0x8CEC,
    COLOR13 = 0x8CED,
    COLOR14 = 0x8CEE,
    COLOR15 = 0x8CEF,
    COLOR16 = 0x8CF0,
    COLOR17 = 0x8CF1,
    COLOR18 = 0x8CF2,
    COLOR19 = 0x8CF3,
    COLOR20 = 0x8CF4,
    COLOR21 = 0x8CF5,
    COLOR22 = 0x8CF6,
    COLOR23 = 0x8CF7,
    COLOR24 = 0x8CF8,
    COLOR25 = 0x8CF9,
    COLOR26 = 0x8CFA,
    COLOR27 = 0x8CFB,
    COLOR28 = 0x8CFC,
    COLOR29 = 0x8CFD,
    COLOR30 = 0x8CFE,
    COLOR31 = 0x8CFF,
};

class DGLFramebuffer : DGLObject
{
  public:
    static unsigned int MAX_COLOR_ATTACHMENTS() { return GL_MAX_COLOR_ATTACHMENTS; }
    static FramebufferAttachment GetColorAttachment(unsigned int i) {
        assert(i < MAX_COLOR_ATTACHMENTS());
        return (FramebufferAttachment)((unsigned int)FramebufferAttachment::COLOR0 + 1);
    }
    static GLint CurrentFramebufferID(FramebufferType type = FramebufferType::FRAMEBUFFER);
    static void BindDefaultFramebuffer(FramebufferType type = FramebufferType::FRAMEBUFFER) {
        glBindFramebuffer((GLenum)type, 0);
    }

  public:
    void Init();
    void Bind(FramebufferType type = FramebufferType::FRAMEBUFFER);
    void Attach(DGLTexture2D* tex, FramebufferAttachment attachment = FramebufferAttachment::COLOR0, int texlayer = 0);
    void Dettach(FramebufferAttachment attachment = FramebufferAttachment::COLOR0);
  protected:
    virtual void OnRelease();
};

}
