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

// NOTE: VAO in OpenGL
class DGLVertexAttributeSet : public DGLObject
{
  public:
    void Init(std::initializer_list<Attribute> attribs);
    void AttachVertexBuffer(DGLBuffer* vert_buffer);
    void AttachIndexBuffer(DGLBuffer* ind_buffer);
    void Bind();
  private:
    std::vector<Attribute> attributes;
    size_t total_size_b = 0;
  protected:
    virtual void OnRelease();
};

class Geometry : public DGLObject
{
  public:
    void Init();
  protected:
    virtual void OnRelease();

};

}
