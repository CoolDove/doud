#pragma once
#include <string>
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
    void Init(int count, ... );
    void Bind();
  protected:
    virtual void OnRelease();
};

}
