#include "CloudGenerator.h"
#include "DoveLog.hpp"

CloudGenerator::CloudGenerator(DGLRepository* repo) {
    tex.Init();
    tex.Allocate(2048, 2048);
    glrepo = repo;

    fbuf.Init();
}

CloudGenerator::~CloudGenerator() {
    tex.Release();
}

void CloudGenerator::Generate() {
    DLOG_DEBUG("generating...");
    using namespace DGL;

    fbuf.Bind();
    fbuf.Attach(&tex);
    SetViewport(0, 0, 2048, 2048);
    SetClearColor({ 0.8f, 0.2f, 0.3f, 1.0f });
    ClearFramebuffer(ClearMask::COLOR);

    DGLGeometry* geom_quad = glrepo->GetGeometry("unit_quad");
    DGLShader* shader = glrepo->GetShader("test");
    DGLTexture2D* tex_noise = glrepo->GetTexture2D("jko");
    DGLVertexAttributeSet* vas_p3 = glrepo->GetVertexAttributeSet("P2U2");
    if (geom_quad && shader && vas_p3) {
        vas_p3->AttachGeometry(geom_quad);
        vas_p3->Bind();

        tex_noise->Bind(0);
        shader->UniformI("noise", 0);

        glDrawElements(GL_TRIANGLES, geom_quad->indices.size(), GL_UNSIGNED_INT, (void*)0);
    } else {
        DLOG_ERROR("resources missing in glrepo");
    }

    DLOG_DEBUG("generated");
}
