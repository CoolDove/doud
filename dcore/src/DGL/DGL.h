#pragma once
#include <windows.h>
#include <stdint.h>
#include <glad/glad.h>
#include <gl/GL.h>
#include "glm/glm.hpp"
#include "BitTagEnum.h"

namespace DGL
{
extern bool DGL_INITED;
void InitOpenGL(HWND wnd_handle);

void SetClearColor(glm::vec4 color);

enum class ClearMask : uint32_t {
    COLOR   =  0X00004000,
    DEPTH   =  0X00000100,
    STENCIL =  0X00000400
};
BIT_MASK_ENUM(ClearMask)
void ClearFramebuffer(ClearMask mask);

/* @SetViewPort
*  x, y:
*       Specify the lower left corner of the viewport rectangle, in pixels. The initial value is (0,0).
*  width, height:
*       Specify the width and height of the viewport. When a GL context is first attached to a window,
*       width and height are set to the dimensions of that window.
*/
void SetViewport(int x, int y, int width, int height);

}
