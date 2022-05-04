#include "DGLTexture.h"

namespace DGL
{

void DGLTexture2D::Init() {
    glCreateTextures((GLenum)TexType::TEXTURE_2D, 1, &native_id);
    ParamFilterMag(TexFilter::NEAREST);
    ParamFilterMin(TexFilter::NEAREST);

    ParamWrapR(TexWrap::CLAMP_TO_EDGE);
    ParamWrapS(TexWrap::CLAMP_TO_EDGE);
    type_ = TexType::TEXTURE_2D;
}

void DGLTexture2D::Allocate(int width, int height, uint32_t levels, SizedInternalFormat format,
                          PixFormat pix_format, PixType pix_type, void* data)
{
    if (!native_id) return;
    glTextureStorage2D(native_id, levels, (GLenum)format, width, height);
    width_ = width;
    height_ = height;
    format_ = format;
    levels_ = levels;
    allocated_ = true;
}

void DGLTexture2D::Upload(void* data, PixFormat pix_format, PixType pix_type)
{
    if (!native_id) return;
    glTextureSubImage2D(native_id, 0, 0, 0, width_, height_, (GLenum)pix_format, (GLenum)pix_type, data);
}
void DGLTexture2D::Upload(void* data, int offsetx, int offsety, int width, int height, int level,
                          PixFormat pix_format, PixType pix_type)
{
    if (!native_id) return;
    glTextureSubImage2D(native_id, level, offsetx, offsety, width, height, (GLenum)pix_format, (GLenum)pix_type, data);
}

void DGLTexture2D::Bind(uint32_t unit) {
    if (native_id) glBindTextureUnit(unit, native_id);
}
void DGLTexture2D::BindImage(uint32_t unit, uint32_t level, bool layered, int layer,
                             Access acc, ImageUnitFormat format)
{
    if (native_id) glBindImageTexture(unit, native_id, level, layered, layer, (GLenum)acc, (GLenum)format);
}

void DGLTexture2D::OnRelease() {
    if (native_id) glDeleteTextures(1, &native_id);
}

}
