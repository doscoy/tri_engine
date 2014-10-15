#include "gfx/tri_shader.hpp"
#include "platform/platform_sdk.hpp"
#include "dbg/tri_assert.hpp"
#include "dbg/tri_trace.hpp"


namespace t3 {
inline namespace gfx {



Shader::Shader()
    : handle_(0)
    , linked_(false)
    , log_()
    , constant_int_()
    , constant_float_()
    , constant_vec3_()
    , constant_float_array_()
    , constant_float_array_location_{0,0,0,0,0,0,0,0,0}
    , constant_float_array_use_(false)
{
    
}

Shader::Shader(
    const char* vsh,
    const char* fsh
)   : Shader()
{
    build(vsh, fsh);
}


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
    const char* const source,
    RenderSystem::ShaderType type
) {
    if (handle_ <= 0) {
        handle_ = glCreateProgram();
        if (handle_ == 0) {
            log_ = "create shader failed.";
        }
    }
    int shader_handle = RenderSystem::buildShader(source, type);
    T3_ASSERT(shader_handle >= 0);

    RenderSystem::attachShader(
        handle_,
        shader_handle
    );
    
    
    return true;
}


void Shader::build(
    const char* const vsh,
    const char* const fsh
) {
    compileVertexShader(vsh);
    compileFragmentShader(fsh);
    link();
}

void Shader::compileVertexShader(
    const char* const vsh
) {
    compileShaderFromString(vsh, RenderSystem::ShaderType::VERTEX_SHADER);
}

void Shader::compileFragmentShader(
    const char* const fsh
) {
    compileShaderFromString(fsh, RenderSystem::ShaderType::FRAGMENT_SHADER);
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
    T3_NULL_ASSERT(this);
    
    if (handle_ <= 0 || (!linked_)) {
        return false;
    }
    

    //  プログラム設定
    RenderSystem::setShader(handle_);
        
    //  ユニフォーム送信
    //  int レジスタ
    for (auto& i : constant_int_) {
        if (i.use_) {
            t3::RenderSystem::setUniformValue(i.location_, i.value_);
        }
    }

    //  float レジスタ
    for (auto& f : constant_float_) {
        if (f.use_) {
            t3::RenderSystem::setUniformValue(f.location_, f.value_);
        }
    }
    
    //  vec3 レジスタ
    for (auto& v : constant_vec3_) {
        if (v.use_) {
            t3::RenderSystem::setUniformValue(
                v.location_,
                v.value_.x_,
                v.value_.y_,
                v.value_.z_
            );
        }
    }
    
    //  float array　レジスタ
    if (constant_float_array_use_) {
        for (int i = 0; i < constant_float_array_size_; ++i) {
            t3::RenderSystem::setUniformValue(
                constant_float_array_location_[i],
                constant_float_array_[i]
            );
        }
    
    }
    
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
    RenderSystem::setUniformValue(location, x, y, z);
}

void Shader::setUniform(
    const char* const name,
    float x,
    float y,
    float z,
    float w
) {
    int location = getUniformLocation(name);
    RenderSystem::setUniformValue(location, x, y, z, w);
}

void Shader::setUniform(
    const char* const name,
    const Vec3& v
) {
    setUniform(name, v.x_, v.y_, v.z_);
}

void Shader::setUniform(
    const char* const name,
    const Mtx44& m
) {
    int location = getUniformLocation(name);
    RenderSystem::setUniformMatrix(location, m);
}

void Shader::setUniform(
    const char* const name,
    float val
) {
    int location = getUniformLocation(name);
    RenderSystem::setUniformValue(location, val);
}

void Shader::setUniform(
    const char* const name,
    int val
) {
    int location = getUniformLocation(name);
    RenderSystem::setUniformValue(location, val);
}

void Shader::setUniform(
    const char* const name,
    bool val
) {
    int location = getUniformLocation(name);
    RenderSystem::setUniformValue(location, val);
}

void Shader::setAttribute(
    const char* const name,
    float a,
    float b,
    float c,
    float d
) {
    int location = getAttributeLocation(name);
    RenderSystem::setAttributeValue(location, a, b, c, d);
}


int Shader::getUniformLocation(const char* const name) const {
    int location = RenderSystem::getUniformLocation(handle_, name);
    T3_ASSERT_MSG(location >= 0, "name = %s", name);
    return location;
}

int Shader::getAttributeLocation(const char* const name) const {
    int location = RenderSystem::getAttributeLocation(handle_, name);
    T3_ASSERT_MSG(location >= 0, "name = %s", name);
    return location;
}


void Shader::setAttributePointer(
    const char* const name,
    int element_num,
    int type,
    bool normalized,
    int stride,
    void* pointer
) {
    int location = getAttributeLocation(name);
    RenderSystem::setVertexAttributePointer(location, element_num, type, normalized, stride, pointer);
}

void Shader::setEnableAttributeArray(
    const char* const name,
    bool flag
) {
    int location = getAttributeLocation(name);
    
    if (flag) {
        RenderSystem::setEnableVertexAttribute(location);
    }
    else {
        RenderSystem::setDisableVertexAttribute(location);
    }
}



}   // namespace gfx
}   // namespace t3
