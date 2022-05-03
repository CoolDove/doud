#pragma once
#include "DCore.h"
#include <windows.h>
#include "DGL/DGL.h"
#include <unordered_map>
#include "DGLRepository.h"

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
        void BuildDGLRepo();
      private:
        DGLRepository glrepo;
    };
    
    extern App app;
    extern bool app_inited;
}
