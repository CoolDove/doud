#pragma once
#include <string>
#include <unordered_map>
#include "DGLObject.h"

namespace DGL
{
enum class ShaderType : uint32_t {
    FRAGMENT_SHADER        = 0x8B30,
    VERTEX_SHADER          = 0x8B31,
    COMPUTE_SHADER         = 0x91B9,
    TESS_CONTROL_SHADER    = 0x8E88,
    TESS_EVALUATION_SHADER = 0x8E87,
    GEOMETRY_SHADER        = 0x8DD9
};


class DGLNativeShader : public DGLObject
{
  public:
    void Init(ShaderType type);
    void Load(const std::string& path);
    void Compile(const std::string& src);
    ShaderType GetType() const { return type; }
    bool IsGood() const { return good; }
  private:
    ShaderType type;
    bool good;
  protected:
    virtual void OnRelease();
};

class DGLShader : public DGLObject
{
  public:
    void Init(std::initializer_list<DGLNativeShader*> shaders);
    void Bind();
  public:
    // NOTE: you have to manually bind this program before setting uniforms !!!!!!
    void UniformI(const std::string& name, int32_t v0);
    void UniformI(const std::string& name, int32_t v0, int32_t v1);
    void UniformI(const std::string& name, int32_t v0, int32_t v1, int32_t v2);
    void UniformI(const std::string& name, int32_t v0, int32_t v1, int32_t v2, int32_t v3);

    void UniformF(const std::string& name, float v0);
    void UniformF(const std::string& name, float v0, float v1);
    void UniformF(const std::string& name, float v0, float v1, float v2);
    void UniformF(const std::string& name, float v0, float v1, float v2, float v3);

    void UniformUI(const std::string& name, uint32_t v0);
    void UniformUI(const std::string& name, uint32_t v0, uint32_t v1);
    void UniformUI(const std::string& name, uint32_t v0, uint32_t v1, uint32_t v2);
    void UniformUI(const std::string& name, uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3);

    void UniformMat(const std::string& name, uint32_t dimensions, const float* data, bool transpose = false, int count = 1);

  private:
    GLint LocateUniform(const std::string& name);
    std::unordered_map<std::string, GLuint> uniform_location_cache;
  
  protected:
    virtual void OnRelease();
};

}
