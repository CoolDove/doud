#include "DGL.h"
#include <windows.h>
#include <gl/GL.h>

namespace DGL
{

bool DGL_INITED = false;
void InitOpenGL(HWND wnd_handle) {
    HDC device_context = GetDC(wnd_handle);

    PIXELFORMATDESCRIPTOR desired_pixel_format = {};
    desired_pixel_format.nSize      = sizeof(desired_pixel_format);
    desired_pixel_format.nVersion   = 1;
    desired_pixel_format.dwFlags    = PFD_SUPPORT_OPENGL|PFD_DRAW_TO_WINDOW|PFD_DOUBLEBUFFER;
    desired_pixel_format.iPixelType = PFD_TYPE_RGBA;
    desired_pixel_format.cColorBits = 32;
    desired_pixel_format.cAlphaBits = 8;

    PIXELFORMATDESCRIPTOR suggested_pixel_format = {};
    int pixel_format_index = ChoosePixelFormat(device_context, &desired_pixel_format);

    DescribePixelFormat(device_context,
                        pixel_format_index,
                        sizeof(suggested_pixel_format),
                        &suggested_pixel_format);

    SetPixelFormat(device_context, pixel_format_index, &suggested_pixel_format);

    HGLRC gl_context = wglCreateContext(device_context);
    wglMakeCurrent(device_context, gl_context);

    gladLoadGL();
    // gl_info.version              = (char*)glGetString(GL_VERSION);
    // gl_info.vendor               = (char*)glGetString(GL_VENDOR);
    // gl_info.renderer             = (char*)glGetString(GL_RENDERER);
    // gl_info.shading_lang_version = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
    DGL_INITED = true;
}
}
