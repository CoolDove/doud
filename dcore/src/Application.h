#pragma once
#include "DCore.h"
#include <windows.h>

namespace Application
{
    DCORE void InitApp(HINSTANCE instance, TCHAR* cmd_line);
    DCORE void Run();

    class App
    {
        public:
        App(TCHAR* cmd_line);
        ~App();

        void Run();
        void Draw();
        
        int width = 0;
        int height = 0;
    };
    
    extern App app;
    extern bool app_inited;
}
