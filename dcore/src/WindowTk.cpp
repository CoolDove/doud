#include "WindowTk.h"
#include <tchar.h>

namespace WindowTk
{

HWND window_handle = 0;

LRESULT CALLBACK wnd_proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    LRESULT result = 0;
    switch (message)
    {
        case WM_PAINT: {
            HDC dc_handle;
            PAINTSTRUCT ps;
            dc_handle = BeginPaint(window_handle, &ps);
            RECT rect = {0, 0, 800, 600};
            SetTextColor(dc_handle, RGB(0, 0, 255));
            TCHAR* text = _T("Hello Cloud | 你好 云朵");
            DrawText(dc_handle, text, _tcslen(text), &rect, DT_CENTER | DT_VCENTER);
            EndPaint(window_handle, &ps);
        } break;
        case WM_CLOSE: {
            DestroyWindow(window);
        } break;
        case WM_DESTROY: {
            PostQuitMessage(0);
        } break;
        default:
        {
            result = DefWindowProc(window, message, wparam, lparam);
        } break;
    }
    return result;
}

void DWTKCreateWindow(HINSTANCE instance, TCHAR* cmd_line, int show_code) {
    WNDCLASS wnd_class = {};
    wnd_class.style = CS_HREDRAW | CS_VREDRAW;
    wnd_class.lpfnWndProc = wnd_proc;
    wnd_class.hInstance = instance;
    wnd_class.lpszClassName = _T("DoudWindowClass");

    RegisterClass(&wnd_class);

    window_handle = CreateWindowEx(0, wnd_class.lpszClassName,
                            _T("Doud"),
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
    UpdateWindow(window_handle);
}

void DWTKRun() {
    MSG msg;
    while (BOOL result = GetMessage(&msg, nullptr, 0, 0)) {
        if (result > 0) {
            // @Update:
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            break;
        }
    }
}

}
