#ifdef DOVE_CPP_NATIVE
#include <windows.h>
#include <stdio.h>
#include "WindowTk.h"
#include "DCore.h"
#include <tchar.h>
#include "DGL/DGL.h"
#include "APplication.h"

int wWinMain(HINSTANCE instance, HINSTANCE prev_instance, TCHAR* cmd_line, int show_code) {
    Application::InitApp(instance, cmd_line);
    Application::Run();
    Application::ReleaseApp();
};
#endif
