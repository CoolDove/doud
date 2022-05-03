#include "DGLRepository.h"

DGLRepository::~DGLRepository()
{
    for (auto ite = vattrib_sets.begin(); ite != vattrib_sets.end(); ite++)
    {
        delete ite->second;
    }
    for (auto ite = shaders.begin(); ite != shaders.end(); ite++) {
        delete ite->second;
    }
    for (auto ite = geometries.begin(); ite != geometries.end(); ite++) {
        delete ite->second;
    }
}

void DGLRepository::PushVertexAttributeSet(const std::string& name, DGL::DGLVertexAttributeSet* vaset) {
    if (vattrib_sets.find(name) != vattrib_sets.end()) return;
    vattrib_sets[name] = vaset;
}
void DGLRepository::PushShader(const std::string& name, DGL::DGLShader* shader) {
    if (shaders.find(name) != shaders.end()) return;
    shaders[name] = shader;
}
void DGLRepository::PushGeometry(const std::string& name, DGL::DGLGeometry* geom) {
    if (geometries.find(name) != geometries.end()) return;
    geometries[name] = geom;
}

DGL::DGLVertexAttributeSet* DGLRepository::DGLRepository::GetVertexAttributeSet(const std::string& name) {
    if (vattrib_sets.find(name) == vattrib_sets.end()) return nullptr;
    return vattrib_sets[name];
}
DGL::DGLShader* DGLRepository::GetShader(const std::string& name) {
    if (shaders.find(name) == shaders.end()) return nullptr;
    return shaders[name];
}
DGL::DGLGeometry* DGLRepository::GetGeometry(const std::string& name) {
    if (geometries.find(name) == geometries.end()) return nullptr;
    return geometries[name];
}

