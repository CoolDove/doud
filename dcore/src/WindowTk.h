#pragma once
#include "DCore.h"
#include <windows.h>
#include <tchar.h>

namespace WindowTk
{
using WndProc = LRESULT(*)(HWND window, UINT message, WPARAM wparam, LPARAM lparam);

extern HWND window_handle;

void DWTKCreateWindow(HINSTANCE instance, TCHAR* cmd_line, WndProc wnd_proc, int show_code);
void DWTKProcessWindowEvent(MSG* msg);

}
