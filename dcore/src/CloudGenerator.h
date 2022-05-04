#pragma once
#include "DGL/DGL.h"
#include "DGLRepository.h"

class CloudGenerator
{
  public:
    CloudGenerator(DGLRepository* repo);
    ~CloudGenerator();
    void Generate();
    DGL::DGLTexture2D* CloudTex() { return &tex; }
  private:
    DGL::DGLTexture2D tex;
    DGL::DGLFramebuffer fbuf;
    DGLRepository* glrepo;
};
