#include "Application.h"
#include "WindowTk.h"
#include "DGL/DGL.h"
#include "DoveLog.hpp"

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

        DLOG_ON_PUSH = [](const Dove::LogMsg& _msg){
            OutputDebugStringA(_msg.to_string(Dove::DMSG_FLAG_SIMPLE | Dove::DMSG_FLAG_FILE | Dove::DMSG_FLAG_LINE).c_str());
            OutputDebugStringA("\n");
        };
        DLOG_INIT;

        APP = new App(cmd_line);
        WindowTk::DWTKCreateWindow(instance, cmd_line, AppWndProc,1);
        DGL::InitOpenGL(WindowTk::window_handle);
        app_inited = true;

        APP->Init();
    }
    void Run() {
        if (app_inited) APP->Run();
    }
    void ReleaseApp() {
        delete APP;
        DLOG_CLOSE;
    }

    App::App(TCHAR* cmd_line) {
        // TODO:
    }

    App::~App() {
        ebuf.Release();
        vbuf.Release();
        shader.Release();
    }

    void App::Init() {
        vbuf.Init();
        ebuf.Init();

        using namespace DGL;
        // glCreateVertexArrays(1, &vao);
// 
        // glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, false, 0);
        // glVertexArrayAttribBinding(vao, 0, 0);
        // glEnableVertexArrayAttrib(vao, 0);
// 
        // glVertexArrayVertexBuffer(vao, 0, vbuf.GetNativeID(), 0, 3 * sizeof(float));
        // glVertexArrayElementBuffer(vao, ebuf.GetNativeID());

        attrib_set.Init({ {Attribute::Type::POSITION, 3} });

        float vbuf_data[] = {
            0.0,  0.5, 0.0,
           -0.5, -0.5, 0.0,
            0.5, -0.5, 0.0
        };
        vbuf.Allocate(3 * 3 * sizeof(float), BufFlag::DYNAMIC_STORAGE_BIT | BufFlag::MAP_READ_BIT);
        vbuf.Upload(3 * 3 * sizeof(float), 0, vbuf_data);

        int ebuf_data[] = { 0, 1, 2 };
        ebuf.Allocate(3 * sizeof(uint32_t), BufFlag::DYNAMIC_STORAGE_BIT | BufFlag::MAP_READ_BIT);
        ebuf.Upload(3 * sizeof(uint32_t), 0, ebuf_data);

        DGLNativeShader vert;
        vert.Init(ShaderType::VERTEX_SHADER);
        vert.Load("./res/shaders/test.vert");
        DGLNativeShader frag;
        frag.Init(ShaderType::FRAGMENT_SHADER);
        frag.Load("./res/shaders/test.frag");

        shader.Init(2, &vert, &frag);
        shader.Bind();
        vert.Release();
        frag.Release();
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

                shader.Bind();
                attrib_set.AttachVertexBuffer(&vbuf);
                attrib_set.AttachIndexBuffer(&ebuf);
                attrib_set.Bind();
                
                glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
            }
            SwapBuffers(hdc);
        }
    }

}
