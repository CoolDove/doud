#pragma once
#include "DGLObject.h"
#include "DGLBuffer.h"
#include "vector"

namespace DGL
{
struct Attribute {
    enum Type {
        POSITION,
        COLOR,
        UV,
        NORMAL
    } type;
    int dimension;
};

struct DGLVertex {
    glm::vec4 position;
    glm::vec2 uv0;
    glm::vec2 uv1;
    glm::vec2 uv2;
    glm::vec4 color0;
    glm::vec4 color1;
    glm::vec4 color2;
    glm::vec4 normal0;
    glm::vec4 normal1;
    glm::vec4 normal2;
};

class DGLGeometry : public DGLObject
{
  public:
    void Upload();

    void SetAttributes(std::initializer_list<Attribute> attribs);
    size_t GetVertexDataStride();
    DGLBuffer* GetVertexBuffer() { return &vbuf; }
    DGLBuffer* GetIndexBuffer() { return &ibuf; }
    std::vector<unsigned int> indices;
    std::vector<DGLVertex> vertices;
  private:
    DGLBuffer vbuf;
    DGLBuffer ibuf;
    std::vector<Attribute> attributes;
  protected:
    virtual void OnRelease();
};

// NOTE: VAO in OpenGL
class DGLVertexAttributeSet : public DGLObject
{
  public:
    void Init(std::initializer_list<Attribute> attribs);
    void AttachVertexBuffer(DGLBuffer* vert_buffer);
    void AttachIndexBuffer(DGLBuffer* ind_buffer);
    void AttachGeometry(DGLGeometry* geom);
    void Bind();
  private:
    std::vector<Attribute> attributes;
    size_t total_size_b = 0;
  protected:
    virtual void OnRelease();
};


}
