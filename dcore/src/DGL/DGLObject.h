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
    void Init();
    void Release();

    int GetNativeID() { return native_id; }
    bool IsInited() { return native_id != 0; }
  protected:
    virtual void OnInit() = 0;
    virtual void OnRelease() = 0;
  protected:
    int native_id = 0;
};

}
