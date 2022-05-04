#include "DUI.h"
#include <stack>

namespace DUI
{
std::stack<DUILayoutContext> contexts;

DUIContext context;

DGL::DGLShader* DUIShader_uielements = nullptr;
DGL::DGLVertexAttributeSet* DUIVas_uivas = nullptr;
DGL::DGLGeometry* DUIGeom_uiquad = nullptr;

void Init() {
    using namespace DGL;
    {
        DUIVas_uivas = new DGLVertexAttributeSet();
        DUIVas_uivas->Init({ {Attribute::Type::POSITION, 2}, {Attribute::Type::UV, 2} });
    }
    {
        DGLNativeShader vert, frag;
        vert.Init(ShaderType::VERTEX_SHADER);
        vert.Load("./res/shaders/uielem.vert");
        frag.Init(ShaderType::FRAGMENT_SHADER);
        frag.Load("./res/shaders/uielem.frag");
        DUIShader_uielements = new DGLShader();
        DUIShader_uielements->Init({ &vert, &frag });
    }
    {
        DUIGeom_uiquad = new DGLGeometry();
        DUIGeom_uiquad->SetAttributes({ {Attribute::Type::POSITION, 2}, {Attribute::Type::UV, 2} });
        for (int i = 0; i < 4; i++) DUIGeom_uiquad->vertices.emplace_back();
        DUIGeom_uiquad->vertices[0].position = { 0.0f, 0.0f, 0.0f, 1.0f };
        DUIGeom_uiquad->vertices[0].uv0 = { 0.0f, 0.0f };
        DUIGeom_uiquad->vertices[1].position = { 1.0f,  0.0f, 0.0f, 1.0f };
        DUIGeom_uiquad->vertices[1].uv0 = { 1.0f, 0.0f };
        DUIGeom_uiquad->vertices[2].position = {  1.0f,  1.0f, 0.0f, 1.0f };
        DUIGeom_uiquad->vertices[2].uv0 = { 1.0f, 1.0f };
        DUIGeom_uiquad->vertices[3].position = {  0.0f, 1.0f, 0.0f, 1.0f };
        DUIGeom_uiquad->vertices[3].uv0 = { 0.0f, 1.0f };

        DUIGeom_uiquad->indices.emplace_back(0);
        DUIGeom_uiquad->indices.emplace_back(1);
        DUIGeom_uiquad->indices.emplace_back(2);
        DUIGeom_uiquad->indices.emplace_back(0);
        DUIGeom_uiquad->indices.emplace_back(2);
        DUIGeom_uiquad->indices.emplace_back(3);
        DUIGeom_uiquad->Upload();
    }

}

void Release() {
    delete DUIGeom_uiquad;
    delete DUIShader_uielements;
    delete DUIVas_uivas;
}

DUILayoutContext GetCurrentContext() {
    if (contexts.empty()) return {0};
    return contexts.top();
};

void Begin(float x, float y, float width, float height, float viewport_width, float viewport_height) {
    DUILayoutContext current_context = GetCurrentContext();
    DUILayoutContext new_context;
    new_context.x = x + current_context.x;
    new_context.y = y + current_context.y;
    new_context.width = current_context.width;
    new_context.height = current_context.height;
    contexts.push(new_context);

    context.viewport_width = viewport_width;
    context.viewport_height = viewport_height;

}

void End() {
    if (!contexts.empty()) contexts.pop();
}

void DrawImage(DGL::DGLTexture2D* tex, float x, float y, float width, float height) {
    using namespace DGL;
    DGLShader* shader = DUIShader_uielements;
    DGLVertexAttributeSet* vas = DUIVas_uivas;
    shader->Bind();
    vas->AttachGeometry(DUIGeom_uiquad);
    vas->Bind();
    tex->Bind(0);
    shader->UniformI("tex", 0);

    DUILayoutContext layout = GetCurrentContext();
    shader->UniformF("elem_width", width);
    shader->UniformF("elem_height", height);
    shader->UniformF("elem_x", x + layout.x);
    shader->UniformF("elem_y", y + layout.y);
    shader->UniformF("viewport_width", context.viewport_width);
    shader->UniformF("viewport_height", context.viewport_height);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}

}
