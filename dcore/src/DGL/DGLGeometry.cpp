#include "DGLGeometry.h"
#include "DGLLog.h"
#include "math.h"

namespace DGL
{

void DGLVertexAttributeSet::Init(std::initializer_list<Attribute> attribs) {
    glCreateVertexArrays(1, &native_id);
    int i = 0;
    int offset = 0; // byte offset
    for (auto ite = attribs.begin(); ite != attribs.end(); ite++) {
        glVertexArrayAttribFormat(native_id, i, ite->dimension, GL_FLOAT, false, offset);
        glVertexArrayAttribBinding(native_id, i, 0);
        glEnableVertexArrayAttrib(native_id, i);

        offset += sizeof(float) * ite->dimension;
        i++;
        attributes.push_back(*ite);
    }
    total_size_b = offset;
}
void DGLVertexAttributeSet::AttachVertexBuffer(DGLBuffer* vbuf) {
    if (native_id) glVertexArrayVertexBuffer(native_id, 0, vbuf->GetNativeID(), 0, total_size_b);
}
void DGLVertexAttributeSet::AttachIndexBuffer(DGLBuffer* ibuf) {
    if (native_id) glVertexArrayElementBuffer(native_id, ibuf->GetNativeID());
}
void DGLVertexAttributeSet::Bind() {
    if (native_id) glBindVertexArray(native_id);
}
void DGLVertexAttributeSet::OnRelease() {
    if (native_id) glDeleteVertexArrays(1, &native_id);
    DGLLog("vertex attrib set released");
}


/* >>>>DGLGeometry>>>> */
void DGLGeometry::Init(std::initializer_list<Attribute> attribs) {
    for (auto ite = attribs.begin(); ite != attribs.end(); ite++) {
        attributes.push_back(*ite);
    }
}

void DGLGeometry::OnRelease() {
    vbuf.Release();
    ibuf.Release();
}

size_t DGLGeometry::GetVertexDataStride() {
    int size = 0;
    for (auto ite = attributes.begin(); ite != attributes.end(); ite++) {
        size += ite->dimension * sizeof(float);
    }
    return size;
}

void DGLGeometry::Upload() {
    {// vertex buffer
        if (vbuf.GetNativeID()) vbuf.Release();
        size_t stride_byte = GetVertexDataStride();
        float* vdata = (float*)malloc(stride_byte * vertices.size());
        int current = 0;

        int uv_count = 0;
        int color_count = 0;
        int normal_count = 0;

        for (int i = 0; i < vertices.size(); i++) {
            for (int a = 0; a < attributes.size(); a++) {
                Attribute* atb = &attributes[a];
                Attribute::Type type = atb->type;
                int dimen = atb->dimension;

                float* vertex_data_begin = nullptr;
                int dimension_max = 0;
                switch (type)
                {
                    case Attribute::Type::POSITION: {
                        vertex_data_begin = (float*)&(vertices[i].position);
                        dimension_max = 4;
                    } break;
                    case Attribute::Type::UV: {
                        vertex_data_begin = (float*)&(vertices[i].uv0);
                        vertex_data_begin += uv_count * 2;
                        if (uv_count > 2) uv_count++;
                        dimension_max = 2;
                    } break;
                    case Attribute::Type::COLOR: {
                        vertex_data_begin = (float*)&(vertices[i].color0);
                        vertex_data_begin += color_count * 4;
                        if (color_count < 2) color_count++;
                        dimension_max = 4;
                    } break;
                    case Attribute::Type::NORMAL: {
                        vertex_data_begin = (float*)&(vertices[i].normal0);
                        vertex_data_begin += normal_count * 4;
                        if (normal_count < 2) normal_count++;
                        dimension_max = 4;
                    } break;
                    default: {} break;
                }

                for (int d = 0; d < min(dimen, dimension_max); d++) {
                    vdata[current] = vertex_data_begin[d];
                    current++;
                }
            }
        }
        vbuf.Init();
        vbuf.Allocate(stride_byte * vertices.size(), BufFlag::DYNAMIC_STORAGE_BIT);
        vbuf.Upload(vbuf.GetSizeB(), 0, (void*)vdata);
        free(vdata);
    }

    {// index buffer
        ibuf.Init();
        ibuf.Allocate(indices.size() * sizeof(unsigned int), BufFlag::DYNAMIC_STORAGE_BIT);
        ibuf.Upload(ibuf.GetSizeB(), 0, (void*)indices.data());
    }
}

}
