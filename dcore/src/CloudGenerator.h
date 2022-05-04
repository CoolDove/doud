#include "DGL/DGL.h"

class CloudGenerator
{
  public:
    CloudGenerator();
    ~CloudGenerator();
    void Generate();
    DGL::DGLTexture2D* CloudTex() { return &tex; }
  private:
    DGL::DGLTexture2D tex;
};
