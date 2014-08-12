#ifndef TRI_SHADER_HPP_INCLUDED
#define TRI_SHADER_HPP_INCLUDED


#include <string>
#include "tri_render_system.hpp"
#include "math/tri_vec3.hpp"
#include "math/tri_matrix.hpp"

namespace t3 {


inline namespace gfx {


class Shader {

    
public:
    Shader();
    ~Shader();

public:
    bool compileShaderFromFile(
        const char* file_name,
        RenderSystem::ShaderType type
    );
    
    bool compileShaderFromString(
        const char* const source,
        RenderSystem::ShaderType type
    );
    
    bool link();
    
    bool use();
    
    const std::string& log() const {
        return log_;
    }
    
    int getHandle() const {
        return handle_;
    }
    
    bool isLinked() const {
        return linked_;
    }
    
    void bindAttributeLocation(
        int location,
        const char* const name
    );
    
    void bindFragmentDataLocation(
        int location,
        const char* const name
    );
    
    void setUniform(const char* const name, float x, float y, float z);
    void setUniform(const char* const name, float x, float y, float z, float w);
    void setUniform(const char* const name, const Vec3& v);
    void setUniform(const char* const name, const Mtx44& m);
    void setUniform(const char* const name, float val);
    void setUniform(const char* const name, int val);
    void setUniform(const char* const name, bool val);
    
    void setAttribute(const char* const name, float a, float b, float c, float d);
    
    void setAttributePointer(
        const char* const name,
        int element_num,
        int type,
        bool normalized,
        int stride,
        void* pointer
    );
    
    void setEnableAttributeArray(const char* const name, bool flag);
    
    int getUniformLocation(
        const char* name
    ) const;
    
    int getAttributeLocation(
        const char* name
    ) const;
    
  
private:
    int handle_;
    bool linked_;
    std::string log_;
    
};

using ShaderPtr = std::shared_ptr<Shader>;
    
    
}   // namaspace gfx
}   // namespace t3

#endif // TRI_RESOURCE_MANAGER_HPP_INCLUDED
