#ifndef TRI_SHADER_HPP_INCLUDED
#define TRI_SHADER_HPP_INCLUDED



#include "tri_render_system.hpp"
#include "math/tri_vec3.hpp"
#include "math/tri_matrix.hpp"

namespace t3 {


inline namespace gfx {


class Shader {

    
public:
    Shader();
    Shader(
        const char* const vsh,
        const char* const fsh
    );
    ~Shader();

public:
    void build(
        const char* const vsh,
        const char* const fsh
    );
    void compileVertexShader(const char* const vsh);
    void compileFragmentShader(const char* const fsh);
    bool use();
    
    const String& log() const {
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
    
    void setConstInt(int no, int val) {
        constant_int_[no].value_ = val;
        if (!constant_int_[no].use_) {
            const char* CONST_UNIFORM_NAME[CONST_REGISTER_NUM] = {
                "const_i_0",
                "const_i_1",
                "const_i_2",
                "const_i_3",
                "const_i_4",
                "const_i_5",
            };
            constant_int_[no].location_ = t3::RenderSystem::getUniformLocation(handle_, CONST_UNIFORM_NAME[no]);
        }
        constant_int_[no].use_ = true;
    }
    
    void setConstFloat(int no, float val) {
        constant_float_[no].value_ = val;
        if (!constant_float_[no].use_) {
            const char* CONST_UNIFORM_NAME[CONST_REGISTER_NUM] = {
                "const_f_0",
                "const_f_1",
                "const_f_2",
                "const_f_3",
                "const_f_4",
                "const_f_5",
            };
            constant_float_[no].location_ = t3::RenderSystem::getUniformLocation(handle_, CONST_UNIFORM_NAME[no]);
        }
        constant_float_[no].use_ = true;
    }
  
    void setConstVec3(int no, const Vec3& val) {
        constant_vec3_[no].value_ = val;
        if (!constant_vec3_[no].use_) {
            const char* CONST_UNIFORM_NAME[CONST_REGISTER_NUM] = {
                "const_vec3_0",
                "const_vec3_1",
                "const_vec3_2",
                "const_vec3_3",
                "const_vec3_4",
                "const_vec3_5",
            };
            constant_vec3_[no].location_ = t3::RenderSystem::getUniformLocation(handle_, CONST_UNIFORM_NAME[no]);
        }
        constant_vec3_[no].use_ = true;
    }
  
    void setConstFloatArray(int no, const float* val, size_t size) {
        constant_float_array_size_ = size;
        
        for (int i = 0; i < constant_float_array_size_; ++i) {
            constant_float_array_[i] = val[i];
        }
        
        if (!constant_float_array_use_) {
            const char* CONST_UNIFORM_NAME[9] = {
                "const_fa_0[0]",
                "const_fa_0[1]",
                "const_fa_0[2]",
                "const_fa_0[3]",
                "const_fa_0[4]",
                "const_fa_0[5]",
                "const_fa_0[6]",
                "const_fa_0[7]",
                "const_fa_0[8]"
            };
            
            for (int i = 0; i < constant_float_array_size_; ++i) {
                constant_float_array_location_[i] = t3::RenderSystem::getUniformLocation(
                    handle_,
                    CONST_UNIFORM_NAME[i]
                );
            }
        }
        constant_float_array_use_ = true;
    }


private:
    bool compileShaderFromFile(
        const char* file_name,
        RenderSystem::ShaderType type
    );
    
    bool compileShaderFromString(
        const char* const source,
        RenderSystem::ShaderType type
    );
    
    bool link();


private:
    int handle_;
    bool linked_;
    String log_;
    
    template<typename T>
    struct ConstValue {
        ConstValue()
            : location_(0)
            , value_()
            , use_(false)
        {
        }
    
        int location_;
        T value_;
        bool use_;
    };
    enum {
        CONST_REGISTER_NUM = 9,
    };
    Array<ConstValue<int>, CONST_REGISTER_NUM> constant_int_;
    Array<ConstValue<float>, CONST_REGISTER_NUM> constant_float_;
    Array<ConstValue<Vec3>, CONST_REGISTER_NUM> constant_vec3_;
    
    float constant_float_array_[9];
    bool constant_float_array_use_;
    size_t constant_float_array_size_;
    int constant_float_array_location_[9];
};

using ShaderPtr = SharedPtr<Shader>;
    
    
}   // namaspace gfx
}   // namespace t3

#endif // TRI_RESOURCE_MANAGER_HPP_INCLUDED
