#pragma once
#include "DCore.h"
#include <windows.h>
#include "DGL/DGL.h"
#include <unordered_map>

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

        int width = 0;
        int height = 0;
      private:
        DGL::DGLShader shader;
        DGL::DGLGeometry geo_quad;
        DGL::DGLGeometry geo_triangle;
        std::unordered_map<std::string, DGL::DGLVertexAttributeSet*>
            attrib_sets;
    };
    
    extern App app;
    extern bool app_inited;
}
