﻿#include "Application.h"
#include "WindowTk.h"
#include "DGL/DGL.h"

namespace Application
{
    App* APP = nullptr;
    bool app_inited = false;

    LRESULT AppWndProc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
        LRESULT result = 0;
        switch (message)
        {
            case WM_PAINT: {
                APP->Draw();
            } break;
            case WM_CLOSE: {
                PostQuitMessage(0);
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

    void InitApp(HINSTANCE instance, TCHAR* cmd_line) {
        if (app_inited) return;
        APP = new App(instance, cmd_line);
        app_inited = true;
    }
    void Run() {
        if (app_inited) APP->Run();
    }

    App::App(HINSTANCE instance, TCHAR* cmd_line) {
        WindowTk::DWTKCreateWindow(instance, cmd_line, AppWndProc,1);
        DGL::InitOpenGL(WindowTk::window_handle);
    }

    void App::Run() {
        MSG msg;
        while (BOOL result = GetMessage(&msg, nullptr, 0, 0)) {
            if (result > 0) {
                WindowTk::DWTKProcessWindowEvent(&msg);
            } else {
                break;
            }
        }
    }

    void App::Draw() {
        if (DGL::DGL_INITED) {
            HWND wnd = WindowTk::window_handle;
            HDC hdc = GetDC(wnd);
            {// OpenGL region
                glClearColor(0.5f, 0.2f, 0.8f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                SwapBuffers(hdc);
            }
        }
    }

}
