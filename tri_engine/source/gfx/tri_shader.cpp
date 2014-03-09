#include "tri_shader.hpp"
#include "platform/platform_sdk.hpp"
#include "dbg/tri_assert.hpp"


namespace t3 {
inline namespace gfx {



Shader::Shader()
    : handle_(0)
    , linked_(false)
{}

Shader::~Shader()
{
}


bool Shader::compileShaderFromFile(
    const char *file_name,
    RenderSystem::ShaderType type
) {
    //## 作る
    return false;
}

bool Shader::compileShaderFromString(
    const std::string& source,
    RenderSystem::ShaderType type
) {
    if (handle_ <= 0) {
        handle_ = glCreateProgram();
        if (handle_ == 0) {
            log_ = "create shader failed.";
        }
    }
    int shader_handle = RenderSystem::buildShader(source.c_str(), type);
    if (shader_handle < 0) {
        return false;
    }

    RenderSystem::attachShader(
        handle_,
        shader_handle
    );
    
    
    return true;
}


bool Shader::link() {
    
    if (linked_) {
        return true;
    }
    if (handle_ <= 0) {
        return false;
    }
    
    RenderSystem::linkShader(handle_);
    
    //## 失敗した時のエラーログ取得
    
    linked_ = true;
    
    return linked_;
}

bool Shader::use() {
    
    if (handle_ <= 0 || (!linked_)) {
        return false;
    }
    
    RenderSystem::setShader(handle_);
    return true;
}


void Shader::bindAttributeLocation(
    int location,
    const char* const name
) {
    RenderSystem::bindAttributeLocation(handle_, location, name);
}

void Shader::bindFragmentDataLocation(
    int location,
    const char* const name
) {
    RenderSystem::bindFragmentDataLocation(handle_, location, name);
}

void Shader::setUniform(
    const char* const name,
    float x,
    float y,
    float z
) {
    int location = getUniformLocation(name);
    T3_ASSERT(location >= 0);
    RenderSystem::setUniformValue(location, x, y, z);
}

void Shader::setUniform(
    const char* const name,
    const Vec3& v
) {
    setUniform(name, v.x_, v.y_, v.z_);
}

void Shader::setUniform(
    const char* const name,
    const Mtx4& m
) {
    int location = getUniformLocation(name);
    T3_ASSERT(location >= 0);
    RenderSystem::setUniformMatrix(location, m);
}

void Shader::setUniform(
    const char* const name,
    float val
) {
    int location = getUniformLocation(name);
    T3_ASSERT(location >= 0);
    RenderSystem::setUniformValue(location, val);
}

void Shader::setUniform(
    const char* const name,
    int val
) {
    int location = getUniformLocation(name);
    T3_ASSERT(location >= 0);
    RenderSystem::setUniformValue(location, val);
}

void Shader::setUniform(
    const char* const name,
    bool val
) {
    int location = getUniformLocation(name);
    T3_ASSERT(location >= 0);
    RenderSystem::setUniformValue(location, val);
}


int Shader::getUniformLocation(const char* const name) const {
    return RenderSystem::getUniformLocation(handle_, name);
}

int Shader::getAttributeLocation(const char* const name) const {
    return RenderSystem::getAttributeLocation(handle_, name);
}




}   // namespace gfx
}   // namespace t3
