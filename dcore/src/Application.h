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
        App(HINSTANCE instance, TCHAR* cmd_line);
        ~App();

        void Run();
        void Draw();
    };
    
    extern App app;
    extern bool app_inited;
}
