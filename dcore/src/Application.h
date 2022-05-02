#pragma once
#include "DCore.h"
#include <windows.h>
#include "DGL/DGL.h"

namespace Application
{
    DCORE void InitApp(HINSTANCE instance, TCHAR* cmd_line);
    DCORE void Run();
    DCORE void ReleaseApp();

    class App
    {
        public:
        App(TCHAR* cmd_line);
        ~App();

        void Run();
        void Init();
        void Draw();

        DGL::DGLBuffer vbuf;
        DGL::DGLBuffer ebuf;
        DGL::DGLShader shader;
        DGL::DGLVertexAttributeSet attrib_set;
        
        int width = 0;
        int height = 0;
    };
    
    extern App app;
    extern bool app_inited;
}
