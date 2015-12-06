////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_shader.hpp
    シェーダ.
*/
#ifndef TRI_SHADER_HPP_INCLUDED
#define TRI_SHADER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "cross/cross.hpp"
#include "core/math/tri_vec3.hpp"
#include "core/math/tri_matrix.hpp"


TRI_CORE_NS_BEGIN


///
/// シェーダポインタ
class Shader;
using ShaderPtr = SharedPtr<Shader>;

///
/// シェーダ
class Shader {

public:
    ///
    /// コンストラクタ
    Shader();
    
    ///
    /// コンストラクタ
    Shader(
        const char* const vsh,  ///< 頂点シェーダ
        const char* const fsh   ///< フラグメントシェーダ
    );
    
    ///
    /// デストラクタ
    ~Shader();

public:
    ///
    /// シェーダをビルド
    void build(
        const char* const vsh,  ///< 頂点シェーダ
        const char* const fsh   ///< フラグメントシェーダ
    );
    
    ///
    /// 頂点シェーダをコンパイル
    void compileVertexShader(
        const char* const vsh   ///< 頂点シェーダ
    );
    
    ///
    /// フラグメントシェーダをコンパイル
    void compileFragmentShader(
        const char* const fsh   ///< フラグメントシェーダ
    );
    
    ///
    /// 使用準備
    bool use();
    
    ///
    /// コンパイルログを取得
    const String& log() const {
        return log_;
    }
    
    ///
    /// シェーダハンドル取得
    int getHandle() const {
        return handle_;
    }
    
    ///
    /// リンク済か判定
    bool isLinked() const {
        return linked_;
    }
    
    ///
    /// アトリビュートを設定
    void bindAttributeLocation(
        int location,
        const char* const name
    );
    
    ///
    /// フラグメントデータのロケーションをバインド
    void bindFragmentDataLocation(
        int location,
        const char* const name
    );
    
    ///
    /// ユニフォーム変数を設定
    void setUniform(const char* const name, float x, float y, float z);
    
    ///
    /// ユニフォーム変数を設定
    void setUniform(const char* const name, float x, float y, float z, float w);
    
    ///
    /// ユニフォーム変数を設定
    void setUniform(const char* const name, const Vec3& v);
    
    ///
    /// ユニフォーム変数を設定
    void setUniform(const char* const name, const Mtx44& m);
    
    ///
    /// ユニフォーム変数を設定
    void setUniform(const char* const name, float val);
    
    ///
    /// ユニフォーム変数を設定
    void setUniform(const char* const name, int val);
    
    ///
    /// ユニフォーム変数を設定
    void setUniform(const char* const name, bool val);
    
    ///
    /// アトリビュート変数を設定
    void setAttribute(const char* const name, float a, float b, float c, float d);
    
    ///
    ///アトリビュートポインタを設定
    void setAttributePointer(
        const char* const name,
        int element_num,
        cross::RenderSystem::TypeFormat type,
        bool normalized,
        int stride,
        void* pointer
    );
    
    ///
    /// アトリビュートを有効化
    bool setEnableAttributeArray(
        const char* const name,     ///< アトリビュート変数名
        bool flag                   ///< 設定フラグ
    );
    
    ///
    /// ユニフォーム位置を取得
    int getUniformLocation(
        const char* name
    ) const;
    
    ///
    /// アトリビュート位置を取得
    int getAttributeLocation(
        const char* name
    ) const;
    
    ///
    /// shader用変数 const_i_Xを設定
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
            constant_int_[no].location_ = cross::RenderSystem::getUniformLocation(handle_, CONST_UNIFORM_NAME[no]);
        }
        constant_int_[no].use_ = true;
    }
    
    ///
    /// shader用変数const_f_Xを設定
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
            constant_float_[no].location_ = cross::RenderSystem::getUniformLocation(handle_, CONST_UNIFORM_NAME[no]);
        }
        constant_float_[no].use_ = true;
    }
  
    ///
    /// shader用変数 const_vec3_Xを設定
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
            constant_vec3_[no].location_ = cross::RenderSystem::getUniformLocation(handle_, CONST_UNIFORM_NAME[no]);
        }
        constant_vec3_[no].use_ = true;
    }
  
    ///
    /// シェーダ用float配列 const_fa_0[x]を設定
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
                constant_float_array_location_[i] = cross::RenderSystem::getUniformLocation(
                    handle_,
                    CONST_UNIFORM_NAME[i]
                );
            }
        }
        constant_float_array_use_ = true;
    }


public:
    static ShaderPtr create(const char* const vsh, const char* const fsh);

private:
    ///
    /// ファイルからシェーダをコンパイル
    bool compileShaderFromFile(
        const char* file_name,
        cross::RenderSystem::ShaderType type
    );
    
    ///
    /// 文字列からシェーダをコンパイル
    bool compileShaderFromString(
        const char* const source,
        cross::RenderSystem::ShaderType type
    );
    
    bool link();


private:
    ///
    /// シェーダハンドル
    int handle_;
    
    ///
    /// リンク済フラグ
    bool linked_;
    
    ///
    /// コンパイルログ
    String log_;
    
    ///
    /// const値
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
        CONST_REGISTER_NUM = 9,     ///< constレジスタの数
		FLOAT_ARRAY_SLOT_SIZE = 9   ///< float配列サイズ
    };
    
    ///
    /// intのconst変数設定
    Array<ConstValue<int>, CONST_REGISTER_NUM> constant_int_;
    
    ///
    /// floatのconst変数設定
    Array<ConstValue<float>, CONST_REGISTER_NUM> constant_float_;
    
    ///
    /// Vec3のconst変数設定
    Array<ConstValue<Vec3>, CONST_REGISTER_NUM> constant_vec3_;
    
    ///
    /// float配列設定
    float constant_float_array_[FLOAT_ARRAY_SLOT_SIZE];
    
    ///
    /// float配列を使うフラグ
    bool constant_float_array_use_;
    
    ///
    /// float配列のサイズ
    size_t constant_float_array_size_;
    
    ///
    /// float配列のシェーダ上のロケーション
    int constant_float_array_location_[FLOAT_ARRAY_SLOT_SIZE];
};


    
TRI_CORE_NS_END

#endif // TRI_RESOURCE_MANAGER_HPP_INCLUDED
