#include "DGLObject.h"

namespace DGL
{
void DGLObject::Release() {
    OnRelease();
    native_id = 0;
}

}
