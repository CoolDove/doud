#pragma once
#include "DGLObject.h"
#include "BitTagEnum.h"

namespace DGL
{
enum class BufFlag : uint32_t {
    DYNAMIC_STORAGE_BIT = 0x0100,
    MAP_READ_BIT        = 0x0001,
    MAP_WRITE_BIT       = 0x0002,
    // MAP_READ_WRITE_BIT  = 0x0003,  // dove defined
    MAP_PERSISTENT_BIT  = 0x0040,  // haven't figure out how to use this
    MAP_COHERENT_BIT    = 0x0080,  // haven't figure out how to use this
    CLIENT_STORAGE_BIT  = 0x0200,
};
BIT_MASK_ENUM(BufFlag)

enum class BufType : uint32_t {
    VERTEX_BUFFER             = 0x8892,
    COPY_READ_BUFFER          = 0x8F36,
    COPY_WRITE_BUFFER         = 0x8F37,
    DRAW_INDIRECT_BUFFER      = 0x8F3F,
    ELEMENT_INDEX_BUFFER      = 0x8893,
    PIXEL_PACK_BUFFER         = 0x88EB,
    PIXEL_UNPACK_BUFFER       = 0x88EC,
    TEXTURE_BUFFER            = 0x8C2A,
    UNIFORM_BUFFER            = 0x8A11,
    TRANSFORM_FEEDBACK_BUFFER = 0x8C8E
};
class DGLBuffer : public DGLObject
{
  public:
    void Init();
    void Allocate(size_t size_b, BufFlag flag);
    void Upload(size_t size_b, size_t offset_b, void* data);
    void Bind(BufType target);
    size_t GetSizeB() const { return buffer_size_b; }
  private:
    size_t buffer_size_b = 0;
    bool allocated = false;
    
  protected:
    virtual void OnRelease();
};

}
