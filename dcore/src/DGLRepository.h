#pragma once
#include <DGL/DGL.h>
#include <unordered_map>
#include <string>


class DGLRepository
{
  public:
    ~DGLRepository();

    void PushVertexAttributeSet(const std::string& name, DGL::DGLVertexAttributeSet* vaset);
    void PushShader(const std::string& name, DGL::DGLShader* shader);
    void PushGeometry(const std::string& name, DGL::DGLGeometry* geom);
    void PushTexture(const std::string& name, DGL::DGLTexture2D* tex);

    DGL::DGLVertexAttributeSet* GetVertexAttributeSet(const std::string& name);
    DGL::DGLShader* GetShader(const std::string& name);
    DGL::DGLGeometry* GetGeometry(const std::string& name);
    DGL::DGLTexture2D* GetTexture2D(const std::string& name);

  private:
    std::unordered_map<std::string, DGL::DGLVertexAttributeSet*>
        vattrib_sets;
    std::unordered_map<std::string, DGL::DGLShader*>
        shaders;
    std::unordered_map<std::string, DGL::DGLGeometry*>
        geometries;
    std::unordered_map<std::string, DGL::DGLTexture2D*>
        textures;
};
