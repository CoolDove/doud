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
                if (DGL::DGL_INITED)
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
        APP->hdc = DGL::InitOpenGL(WindowTk::window_handle);
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
        DLOG_DEBUG("app released");
    }

    void App::BuildDGLRepo() {
        using namespace DGL;
        {// vas
            auto p2u2 = new DGL::DGLVertexAttributeSet();
            p2u2->Init({ {Attribute::Type::POSITION, 2}, {Attribute::Type::UV, 2} });
            auto p3 = new DGL::DGLVertexAttributeSet();
            p3->Init({ {Attribute::Type::POSITION, 3} });

            glrepo.PushVertexAttributeSet("P2U2", p2u2);
            glrepo.PushVertexAttributeSet("P3", p3);
        }
        {// shader
            DGLNativeShader vert;
            vert.Init(ShaderType::VERTEX_SHADER);
            vert.Load("./res/shaders/test.vert");
            DGLNativeShader frag;
            frag.Init(ShaderType::FRAGMENT_SHADER);
            frag.Load("./res/shaders/test.frag");
            DGLShader* shader = new DGLShader();
            shader->Init({ &vert, &frag });
            glrepo.PushShader("test", shader);
        }
        {// geometry
            DGLGeometry* triangle = new DGLGeometry();
            triangle->SetAttributes({ {Attribute::Type::POSITION, 2}, { Attribute::Type::UV, 2 } });
            for (int i = 0; i < 3; i++) triangle->vertices.emplace_back();
            triangle->vertices[0].position = {  0.0f,  0.5f, 0.0f , 1.0f};
            triangle->vertices[0].uv0 = { 0.5f, 1.0f };
            triangle->vertices[1].position = { -0.5f, -0.5f, 0.0f , 1.0f};
            triangle->vertices[1].uv0 = { 0.0f, 0.0f };
            triangle->vertices[2].position = {  0.5f, -0.5f, 0.0f , 1.0f};
            triangle->vertices[2].uv0 = { 1.0f, 0.0f };
            triangle->indices.emplace_back(0);
            triangle->indices.emplace_back(1);
            triangle->indices.emplace_back(2);
            triangle->Upload();

            DGLGeometry* uquad = new DGLGeometry();
            uquad->SetAttributes({ {Attribute::Type::POSITION, 2}, { Attribute::Type::UV, 2 }});
            for (int i = 0; i < 4; i++) uquad->vertices.emplace_back();
            uquad->vertices[0].position = { -0.5f, -0.5f, 0.0f, 1.0f };
            uquad->vertices[0].uv0 = { 0.0f, 0.0f };
            uquad->vertices[1].position = { -0.5f,  0.5f, 0.0f, 1.0f };
            uquad->vertices[1].uv0 = { 0.0f, 1.0f };
            uquad->vertices[2].position = {  0.5f,  0.5f, 0.0f, 1.0f };
            uquad->vertices[2].uv0 = { 1.0f, 1.0f };
            uquad->vertices[3].position = {  0.5f, -0.5f, 0.0f, 1.0f };
            uquad->vertices[3].uv0 = { 1.0f, 0.0f };

            uquad->indices.emplace_back(0);
            uquad->indices.emplace_back(1);
            uquad->indices.emplace_back(2);
            uquad->indices.emplace_back(0);
            uquad->indices.emplace_back(2);
            uquad->indices.emplace_back(3);
            uquad->Upload();

            glrepo.PushGeometry("test_triangle", triangle);
            glrepo.PushGeometry("unit_quad", uquad);
        }
        
    }
    
    void App::Init() {
        BuildDGLRepo();
    }

    void App::Run() {
        MSG msg;
        bool quit = false;
        while (!quit) {
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    quit = true;
                } else {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
        }
    }

    void App::Draw() {
        {
            using namespace DGL;
            SetClearColor({0.3f, 0.7f, 0.9f, 1.0f});
            ClearFramebuffer(ClearMask::COLOR | ClearMask::DEPTH);

            DGLGeometry* geom_quad = glrepo.GetGeometry("unit_quad");
            DGLShader* shader = glrepo.GetShader("test");
            shader->Bind();

            DGLVertexAttributeSet* vas_p3 = glrepo.GetVertexAttributeSet("P2U2");
            if (geom_quad && shader && vas_p3) {
                vas_p3->AttachGeometry(geom_quad);
                vas_p3->Bind();
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
            }
        }
        SwapBuffers(hdc);
    }

}
