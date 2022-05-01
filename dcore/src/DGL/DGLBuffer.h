#include "DGLObject.h"

namespace DGL
{
class DGLBuffer : public DGLObject
{
  protected:
    virtual void OnInit();
    virtual void OnRelease();
};

}
