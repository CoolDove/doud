#include "WindowTk.h"
#include <tchar.h>

namespace WindowTk
{
HWND window_handle = 0;

void DWTKCreateWindow(HINSTANCE instance, TCHAR* cmd_line, WndProc wnd_proc, int show_code) {
    WNDCLASS wnd_class = {};
    wnd_class.style = CS_HREDRAW | CS_VREDRAW;
    wnd_class.lpfnWndProc = wnd_proc;
    wnd_class.hInstance = instance;
    wnd_class.lpszClassName = _T("DoudWindowClass");

    RegisterClass(&wnd_class);

    window_handle = CreateWindowEx(
        0, wnd_class.lpszClassName,
        _T("doud"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 
        CW_USEDEFAULT,
        800, 
        600,
        nullptr, 
        nullptr,
        instance,
        nullptr);
    if (!window_handle) {
        MessageBox(nullptr, _T("failed to create window"), _T("error"), MB_OK);
    }
    
    ShowWindow(window_handle, show_code);
    SwapBuffers(GetDC(window_handle));
    UpdateWindow(window_handle);
}

void DWTKProcessWindowEvent(MSG* msg) {
    TranslateMessage(msg);
    DispatchMessage(msg);
}

}
