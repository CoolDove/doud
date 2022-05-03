#include "DGL.h"
#include <windows.h>
#include <gl/GL.h>
#define WGL_CONTEXT_MAJOR_VERSION_ARB           	0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB           	0x2092
#define WGL_CONTEXT_LAYER_PLANE_ARB             	0x2093
#define WGL_CONTEXT_FLAGS_ARB                   	0x2094
#define WGL_CONTEXT_PROFILE_MASK_ARB            	0x9126
// bits for WGL_CONTEXT_FLAGS_ARB
#define WGL_CONTEXT_DEBUG_BIT_ARB               	0x0001
#define WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB  	0x0002
// bits for WGL_CONTEXT_PROFILE_MASK_ARB
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB        	0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 	0x00000002

namespace DGL
{

bool DGL_INITED = false;
DGLLogFunction DGL_ON_LOG = nullptr;

void DGLLog(const std::string& msg) {
    if (DGL_ON_LOG) DGL_ON_LOG(msg);
}

void SetClearColor(glm::vec4 color) {
    glClearColor(color.r, color.g, color.b, color.a);
}

void ClearFramebuffer(ClearMask mask) {
    glClear((GLbitfield)mask);
}

void SetViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}


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

    using wglCreateContextAttribsARB_t = 
          HGLRC (WINAPI *) (HDC hDC, HGLRC hshareContext, const int *attribList);
    wglCreateContextAttribsARB_t wglCreateContextAttribsARB
        = (wglCreateContextAttribsARB_t)wglGetProcAddress("wglCreateContextAttribsARB");

    if (wglCreateContextAttribsARB) {
        HGLRC share_context = 0;
        int attrib_list[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 5,
#ifdef DEBUG
            WGL_CONTEXT_FLAGS_ARB,         WGL_CONTEXT_DEBUG_BIT_ARB,
#endif
            WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
            0
        };
        HDC dc = GetDC(wnd_handle);
        HGLRC modern_glrc = wglCreateContextAttribsARB(dc, share_context, attrib_list);
        if (modern_glrc) {
            // switch to modern openGL context
            wglMakeCurrent(dc, modern_glrc);
        }

        // NOTE: close the vsync
        typedef void (APIENTRY *PFNWGLEXTSWAPCONTROLPROC) (int);
        PFNWGLEXTSWAPCONTROLPROC wglSwapIntervalEXT = NULL;
        wglSwapIntervalEXT = (PFNWGLEXTSWAPCONTROLPROC)wglGetProcAddress("wglSwapIntervalEXT");
        wglSwapIntervalEXT(0);
        
#ifdef DEBUG
        // gl_debug_init();
#endif
    }
    DGL_INITED = true;
}
}
