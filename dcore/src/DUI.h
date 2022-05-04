#pragma once
#include <DGL/DGL.h>

namespace DUI
{
extern DGL::DGLShader*   DUIShader_uielements;
extern DGL::DGLGeometry* DUIGeom_uiquad;

struct DUILayoutContext
{
    float x;
    float y;
    float width;
    float height;
};

struct DUIContext
{
    float viewport_width;
    float viewport_height;
};

void Init();
void Release();

void Begin(float x, float y, float width, float height, float viewport_width, float viewport_height);
void End();
DUILayoutContext GetCurrentContext();

void DrawImage(DGL::DGLTexture2D* tex, float x, float y, float width, float height);

}
