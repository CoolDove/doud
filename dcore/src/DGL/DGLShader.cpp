#include "DGLShader.h"
#include <ios>
#include <fstream>
#include <windows.h>
#include <stdarg.h>
#include "DoveLog.hpp"

static char* read_file(const char* _path, int* _size = nullptr) {
    std::ifstream file(_path, std::ios_base::in);
    bool good = file.good();
    if (!file.good()) return nullptr;
    
    file.seekg(0, std::ios::end);
    size_t size = file.tellg();
    char* buf = new char[size]();
    file.seekg(0, std::ios::beg);
    file.read(buf, size);
    file.close();
    if (_size != nullptr) *_size = size;
    return buf;
}

namespace DGL
{
/* >>>>DGLNativeShader>>>> */
void DGLNativeShader::Init(ShaderType type) {
    native_id = glCreateShader(static_cast<GLenum>(type));
    this->type = type;
}
void DGLNativeShader::OnRelease() {
    if (native_id) glDeleteShader(native_id);
}
void DGLNativeShader::Load(const std::string& path) {
    char* src = read_file(path.c_str());
    if (src == nullptr) return;
    glShaderSource(native_id, 1, &src, 0);
    Compile(src);
    delete [] src;
}

void DGLNativeShader::Compile(const std::string& src) {
    if (!native_id) {
        DLOG_ERROR("native shader object has not been inited");
        return;
    }
    glCompileShader(native_id);
    GLint compile_tag = 0;
    glGetShaderiv(native_id, GL_COMPILE_STATUS, &compile_tag);
    if (compile_tag == GL_FALSE)
    {
        GLint maxLength = 0;
        GLint returnLength = 0;
        glGetShaderiv(native_id, GL_INFO_LOG_LENGTH, &maxLength);
        char* infoLog = (char*)malloc(maxLength);
        glGetShaderInfoLog(native_id, maxLength, &returnLength, infoLog);
        DLOG_ERROR("native shader error:\n %s", infoLog);
        glDeleteShader(native_id);

        free(infoLog);
    }
}

/* >>>>DGLShader>>>> */
void DGLShader::Init(int count, ... ) {
    native_id = glCreateProgram();

    uint16_t mask = 0u;
    auto check_mask = [&mask](uint16_t _bit_pos){
        if (mask & 1u<<_bit_pos) {
            DLOG_ERROR("trying to link uninited shader");
        } else {
            mask = mask | 1u<<_bit_pos;
        }
    };

    va_list args;
    va_start(args, count); 

    const DGLNativeShader* shader = nullptr;

    for (int i = 0; i < count; i++) {
        shader = va_arg(args, const DGLNativeShader*);

        if (!shader->IsGood()) {
            DLOG_ERROR("shader is not good, failed to link program");
            return;
        }
        
        switch (shader->GetType())
        {
        case ShaderType::FRAGMENT_SHADER:
            check_mask(1); break;
        case ShaderType::VERTEX_SHADER:
            check_mask(2); break;
        case ShaderType::COMPUTE_SHADER:
            check_mask(3); break;
        case ShaderType::TESS_CONTROL_SHADER:
            check_mask(4); break;
        case ShaderType::TESS_EVALUATION_SHADER:
            check_mask(5); break;
        case ShaderType::GEOMETRY_SHADER:
            check_mask(6); break;
        default:
            break;
        }

        glAttachShader(native_id, shader->GetNativeID());
    }
    va_end(args);

    glLinkProgram(native_id);

    GLint status;
    glGetProgramiv(native_id, GL_LINK_STATUS, &status);
    if (!status) {
        DLOG_ERROR("failed to link program");
        Release();
    }
}

void DGLShader::Bind() {
    if (native_id)
        glUseProgram(native_id);
}

void DGLShader::OnRelease() {
    if (native_id) glDeleteProgram(native_id);
}


}
