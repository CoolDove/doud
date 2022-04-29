#pragma once
#include "DCore.h"
#include <windows.h>
#include <tchar.h>

namespace WindowTk
{
extern HWND window_handle;

DCORE void DWTKCreateWindow(HINSTANCE instance, TCHAR* cmd_line, int show_code);
DCORE int DWTKProcessWindowEvent();
void DWTKRun();

}
