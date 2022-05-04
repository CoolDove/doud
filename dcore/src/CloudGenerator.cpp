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
}
