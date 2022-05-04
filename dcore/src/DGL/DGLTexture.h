#pragma once
#include <glad/glad.h>
#include <stdint.h>
#include "DGLEnum.h"
#include "DGLObject.h"
#include <memory>


namespace DGL
{
enum class TexType : uint32_t {
    TEXTURE_1D                   = 0x0DE0,
    TEXTURE_2D                   = 0x0DE1,
    TEXTURE_3D                   = 0x806F,
    TEXTURE_1D_ARRAY             = 0x8C18,
    TEXTURE_2D_ARRAY             = 0x8C1A,
    TEXTURE_RECTANGLE            = 0x84F5,
    TEXTURE_CUBE_MAP             = 0x8513,
    TEXTURE_CUBE_MAP_ARRAY       = 0x9009,
    TEXTURE_BUFFER               = 0x8C2A,
    TEXTURE_2D_MULTISAMPLE       = 0x9100,
    TEXTURE_2D_MULTISAMPLE_ARRAY = 0x9102,
    UNKNOWN                      = 0x0000,
};

enum class PixFormat : uint32_t {
    RED             = 0x1903,
    RG              = 0x8227,
    RGB             = 0x1907,
    BGR             = 0x80E0,

    RGBA            = 0x1908,
    BGRA            = 0x80E1,

    DEPTH_COMPONENT = 0x1902,
    STENCIL_INDEX   = 0x1901,
};

enum class PixType : uint32_t {
    UNSIGNED_BYTE               = 0x1401,
    BYTE                        = 0x1400,

    UNSIGNED_SHORT              = 0x1403,
    SHORT                       = 0x1402,

    UNSIGNED_INT                = 0x1405,
    INT                         = 0x1404,

    FLOAT                       = 0x1406,

    UNSIGNED_BYTE_3_3_2         = 0x8032,
    UNSIGNED_BYTE_2_3_3_REV     = 0x8362,

    UNSIGNED_SHORT_5_6_5        = 0x8363,
    UNSIGNED_SHORT_5_6_5_REV    = 0x8364,

    UNSIGNED_SHORT_4_4_4_4      = 0x8033,
    UNSIGNED_SHORT_4_4_4_4_REV  = 0x8365,

    UNSIGNED_SHORT_5_5_5_1      = 0x8034,
    UNSIGNED_SHORT_1_5_5_5_REV  = 0x8366,

    UNSIGNED_INT_8_8_8_8        = 0x8035,
    UNSIGNED_INT_8_8_8_8_REV    = 0x8367,

    UNSIGNED_INT_10_10_10_2     = 0x8036,
    UNSIGNED_INT_2_10_10_10_REV = 0x8368,
};

enum class TexParam : uint32_t {
    TEXTURE_MIN_FILTER = 0x2801,
    TEXTURE_MAG_FILTER = 0x2800,
    TEXTURE_WRAP_S     = 0x2802,
    TEXTURE_WRAP_T     = 0x2803,
    TEXTURE_WRAP_R     = 0x8072,
};

enum class TexFilter : uint32_t {
    NEAREST = 0x2600,
    LINEAR  = 0x2601,
};

enum class TexWrap : uint32_t {
    CLAMP_TO_EDGE        = 0x812F,
    CLAMP_TO_BORDER      = 0x812D,
    MIRRORED_REPEAT      = 0x8370,
    REPEAT               = 0x2901,
    MIRROR_CLAMP_TO_EDGE = 0x8743,
};

class DGLTexture2D : public DGLObject
{
  public:
    DGLTexture2D() {}
    DGLTexture2D(const DGLTexture2D&) = delete;
    DGLTexture2D* operator=(const DGLTexture2D&) = delete;
    void Init();
    void Allocate(int width, int height, uint32_t levels = 1, SizedInternalFormat format = SizedInternalFormat::RGBA8,
                  PixFormat pix_format = PixFormat::BGRA, PixType pix_type = PixType::UNSIGNED_BYTE, void* data = nullptr);

    // TODO: upload region in texture class
    // void upload_region(uint32_t _level, Dove::IRect2D _region, Dove::IVector2D _src_info, ...);
    void Upload(void* data, PixFormat pix_format = PixFormat::RGBA, PixType pix_type = PixType::UNSIGNED_BYTE);
    void Upload(void* data, int offsetx, int offsety, int width, int height, int level, PixFormat pix_format = PixFormat::RGBA, PixType pix_type = PixType::UNSIGNED_BYTE);
    void Bind(uint32_t unit);
    void BindImage(uint32_t unit, uint32_t level, bool layered, int layer,
                   Access acc, ImageUnitFormat format);

    // void* MemAlloc();
    // void* MemFetch();
    // void MemRelease();
    // void* MemPixels();
  public:
    void ParamFilterMin(TexFilter filter) {glTextureParameteri(native_id, (GLenum)TexParam::TEXTURE_MIN_FILTER, (GLenum)filter);}
    void ParamFilterMag(TexFilter filter) {glTextureParameteri(native_id, (GLenum)TexParam::TEXTURE_MAG_FILTER, (GLenum)filter);}
    void ParamWrapR(TexWrap wrap) {glTextureParameteri(native_id, (GLenum)TexParam::TEXTURE_WRAP_R, (GLenum)wrap);}
    void ParamWrapS(TexWrap wrap) {glTextureParameteri(native_id, (GLenum)TexParam::TEXTURE_WRAP_S, (GLenum)wrap);}
    void ParamWrapT(TexWrap wrap) {glTextureParameteri(native_id, (GLenum)TexParam::TEXTURE_WRAP_T, (GLenum)wrap);}
  public:
    uint32_t width_;
    uint32_t height_;
    SizedInternalFormat format_;
    uint32_t levels_;
    TexType  GetType() const { return type_; }
  private:
    void* pixels_ = nullptr;
    size_t GetDataSize() { return width_ * height_ * 4 * sizeof(uint32_t); }
  private:
    bool    allocated_ = false;
    TexType type_ = TexType::TEXTURE_2D;
  protected:
    virtual void OnRelease();
};

}
