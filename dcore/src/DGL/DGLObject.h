#pragma once
#include <glad/glad.h>
#include <gl/GL.h>
#include "glm/glm.hpp"
#include "BitTagEnum.h"

namespace DGL
{
class DGLObject
{
  public:
    ~DGLObject() {
        Release();
    }
    void Release();

    unsigned int GetNativeID() const { return native_id; }
    bool IsInited() { return native_id != 0; }
  protected:
    virtual void OnRelease() { }
  protected:
    unsigned int native_id = 0;
};

}
