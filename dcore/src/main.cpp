#ifdef DOVE_CPP_NATIVE
#include <windows.h>
#include <stdio.h>
#include "WindowTk.h"
#include "DCore.h"
#include <tchar.h>

int wWinMain(HINSTANCE instance, HINSTANCE prev_instance, TCHAR* cmd_line, int show_code) {
    WindowTk::DWTKCreateWindow(instance, cmd_line, show_code);
    WindowTk::DWTKRun();
};
#endif
