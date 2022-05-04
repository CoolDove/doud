#pragma once
#include "DCore.h"
#include <windows.h>
#include "DGL/DGL.h"
#include <unordered_map>
#include "DGLRepository.h"
#include "CloudGenerator.h"

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

        void Update();
        void Draw();

        void GenerateCloud();

        const int GameMargin = 20;
        const int GamePicSize = 600;
        const int GameWidth = 600;
        const int GameHeight = 1024;

        int width = 0;
        int height = 0;
        HDC hdc;
      private:
        void BuildDGLRepo();
      private:
        DGLRepository glrepo;
        CloudGenerator* cloud = nullptr;
    };
    
    extern App app;
    extern bool app_inited;
}
