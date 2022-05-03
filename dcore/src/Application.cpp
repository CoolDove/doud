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
        DGL::DGL_ON_LOG = [](const std::string& msg) {
            OutputDebugStringA(msg.c_str());
        };
        
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
        shader.Release();
        geo_quad.Release();
        geo_triangle.Release();
        for (auto attribs : attrib_sets) delete attribs.second;
    }

    void App::Init() {
        using namespace DGL;

        attrib_sets.emplace("P2U2", new DGL::DGLVertexAttributeSet());
        attrib_sets.emplace("P3", new DGL::DGLVertexAttributeSet());
        attrib_sets["P2U2"]->Init({ {Attribute::Type::POSITION, 2}, {Attribute::Type::UV, 2} });
        attrib_sets["P3"]->Init({ {Attribute::Type::POSITION, 3} });

        geo_triangle.Init({ {Attribute::Type::POSITION, 3} });
        geo_triangle.vertices.emplace_back();
        geo_triangle.vertices.emplace_back();
        geo_triangle.vertices.emplace_back();
        geo_triangle.vertices[0].position = {  0.0f,  0.5f, 0.0f , 1.0f};
        geo_triangle.vertices[1].position = { -0.5f, -0.5f, 0.0f , 1.0f};
        geo_triangle.vertices[2].position = {  0.5f, -0.5f, 0.0f , 1.0f};

        geo_triangle.indices.emplace_back(0);
        geo_triangle.indices.emplace_back(1);
        geo_triangle.indices.emplace_back(2);
        geo_triangle.Upload();

        DGLNativeShader vert;
        vert.Init(ShaderType::VERTEX_SHADER);
        vert.Load("./res/shaders/test.vert");
        DGLNativeShader frag;
        frag.Init(ShaderType::FRAGMENT_SHADER);
        frag.Load("./res/shaders/test.frag");

        shader.Init({ &vert, &frag });
        shader.Bind();
        vert.Release();
        frag.Release();
    }

    void App::Run() {
        MSG msg;
        while (BOOL result = GetMessage(&msg, nullptr, 0, 0)) {
            if (result > 0) {
                WindowTk::DWTKProcessWindowEvent(&msg);
                if (DGL::DGL_INITED)
                    Draw();
            } else {
                break;
            }
        }
    }

    void App::Draw() {
        HWND wnd = WindowTk::window_handle;
        HDC hdc = GetDC(wnd);
        {
            using namespace DGL;
            SetClearColor({0.3f, 0.7f, 0.9f, 1.0f});
            ClearFramebuffer(ClearMask::COLOR | ClearMask::DEPTH);

            shader.Bind();
            attrib_sets["P3"]->AttachVertexBuffer(&geo_triangle.vbuf);
            attrib_sets["P3"]->AttachIndexBuffer(&geo_triangle.ibuf);
            attrib_sets["P3"]->Bind();

            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0);
        }
        SwapBuffers(hdc);
    }

}
