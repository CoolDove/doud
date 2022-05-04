#include "DGLShader.h"
#include <ios>
#include <fstream>
#include <windows.h>
#include <stdarg.h>
#include "DGLLog.h"

static char* read_file(const char* _path, size_t* _size = nullptr) {
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
        DGLLog("native shader object has not been inited");
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
        DGLLog("native shader error:");
        DGLLog(infoLog);
        DGLLog("\n");
        glDeleteShader(native_id);

        free(infoLog);
    }
}

/* >>>>DGLShader>>>> */
void DGLShader::Init(std::initializer_list<DGLNativeShader*> shaders) {
    native_id = glCreateProgram();

    uint16_t mask = 0u;
    auto check_mask = [&mask](uint16_t _bit_pos){
        if (mask & 1u<<_bit_pos) {
            DGLLog("trying to link uninited shader");
        } else {
            mask = mask | 1u<<_bit_pos;
        }
    };

    int i = 0;
    for (auto ite = shaders.begin(); ite != shaders.end(); ite++) {
        const DGLNativeShader* shader = *ite;

        if (!shader->IsGood()) {
            DGLLog("shader is not good, failed to link program");
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

    glLinkProgram(native_id);

    GLint status;
    glGetProgramiv(native_id, GL_LINK_STATUS, &status);
    if (!status) {
        DGLLog("failed to link program");
        Release();
    }
}

GLint DGLShader::LocateUniform(const std::string& name) {
    if (uniform_location_cache.find(name) == uniform_location_cache.end()) {
        // we didnt find the location in the cache
        GLuint loc = glGetUniformLocation(native_id, name.c_str());
        if (loc == -1) {
            DGLLog("uniform name: ");
            DGLLog(name.c_str());
            DGLLog(" not found\n");
            return -1;
        }
        uniform_location_cache[name] = loc;
        return loc;
    } else {
        return uniform_location_cache[name];
    }
}

void DGLShader::UniformI(const std::string& name, int32_t v0){
    glUniform1i(LocateUniform(name), v0);
}
void DGLShader::UniformI(const std::string& name, int32_t v0, int32_t v1){
    glUniform2i(LocateUniform(name), v0, v1);
}
void DGLShader::UniformI(const std::string& name, int32_t v0, int32_t v1, int32_t v2){
    glUniform3i(LocateUniform(name), v0, v1, v2);
}
void DGLShader::UniformI(const std::string& name, int32_t v0, int32_t v1, int32_t v2, int32_t v3){
    glUniform4i(LocateUniform(name), v0, v1, v2, v3);
}

void DGLShader::UniformF(const std::string& name, float v0){
    glUniform1f(LocateUniform(name), v0);
}
void DGLShader::UniformF(const std::string& name, float v0, float v1){
    glUniform2f(LocateUniform(name), v0, v1);
}
void DGLShader::UniformF(const std::string& name, float v0, float v1, float v2){
    glUniform3f(LocateUniform(name), v0, v1, v2);
}
void DGLShader::UniformF(const std::string& name, float v0, float v1, float v2, float v3){
    glUniform4f(LocateUniform(name), v0, v1, v2, v3);
}

void DGLShader::UniformUI(const std::string& _name, uint32_t v0){
    glUniform1ui(LocateUniform(_name), v0);
}
void DGLShader::UniformUI(const std::string& _name, uint32_t v0, uint32_t v1){
    glUniform2ui(LocateUniform(_name), v0, v1);
}
void DGLShader::UniformUI(const std::string& _name, uint32_t v0, uint32_t v1, uint32_t v2){
    glUniform3ui(LocateUniform(_name), v0, v1, v2);
}
void DGLShader::UniformUI(const std::string& _name, uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3){
    glUniform4ui(LocateUniform(_name), v0, v1, v2, v3);
}

void DGLShader::UniformMat(const std::string& name, uint32_t dimensions, const float* data, bool transpose, int count){
    if (dimensions > 4) dimensions = 4;
    if (dimensions < 2) dimensions = 2;

    switch (dimensions)
    {
    case 2:
        glUniformMatrix2fv(LocateUniform(name), count, transpose, data);
        break;
    case 3:
        glUniformMatrix3fv(LocateUniform(name), count, transpose, data);
        break;
    case 4:
        glUniformMatrix4fv(LocateUniform(name), count, transpose, data);
        break;
    default:
        break;
    }
}

void DGLShader::Bind() {
    if (native_id) glUseProgram(native_id);
}

void DGLShader::OnRelease() {
    if (native_id) glDeleteProgram(native_id);
}


}
