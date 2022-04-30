#pragma once
#include <windows.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace DGL
{
extern bool DGL_INITED;
void InitOpenGL(HWND wnd_handle);

}
