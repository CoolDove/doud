#include "Application.h"
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
            case WM_SIZE: {
                APP->width = LOWORD(lparam);
                APP->height = HIWORD(lparam);
                if (DGL::DGL_INITED) DGL::SetViewport(0, 0, APP->width, APP->height);
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

        APP = new App(cmd_line);
        WindowTk::DWTKCreateWindow(instance, cmd_line, AppWndProc,1);
        DGL::InitOpenGL(WindowTk::window_handle);
        app_inited = true;
    }
    void Run() {
        if (app_inited) APP->Run();
    }
    void ReleaseApp() {
    }

    App::App(TCHAR* cmd_line) {
        // TODO:
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
            {
                using namespace DGL;
                SetClearColor({0.9f, 0.4f, 0.8f, 1.0f});
                ClearFramebuffer(ClearMask::COLOR | ClearMask::DEPTH);
            }
            SwapBuffers(hdc);
        }
    }

}
