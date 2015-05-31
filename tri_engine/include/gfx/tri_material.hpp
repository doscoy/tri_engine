/**
    @file tri_material.hpp
    マテリアル.
*/

#ifndef TRI_MATERIAL_HPP_INCLUDED
#define TRI_MATERIAL_HPP_INCLUDED

//  include
#include "tri_color.hpp"
#include "tri_texture.hpp"



namespace t3 {

class Material;
using MaterialPtr = SharedPtr<Material>;


///
/// マテリアル
class Material
{

    ///
    /// コンストラクタ
    Material()
        : diffuse_()
        , ambient_()
        , opacity_(255)
    {}

public:
    
    ///
    /// デストラクタ
    ~Material()
    {}

public:
    ///
    /// 透明度を持っているか
    bool hasAlpha() const {
        return opacity_ < 255;
    }
    
    ///
    /// 透明度取得
    uint8_t getOpacity() const {
        return opacity_;
    }
    
    ///
    /// 透明度設定
    void setOpacity(int opacity) {
        opacity_ = opacity;
    }
    
    ///
    /// 使用
    void use() {
    
    }

    ///
    /// マテリアル名を取得
    String name() {
        return material_name_;
    }
    
    ///
    /// テクスチャを取得
    TexturePtr texture() {
        return texture_;
    }


    ///
    /// マテリアル生成
    static MaterialPtr create();

    ///
    /// マテリアル生成
    static MaterialPtr create(const char* const material_file_path);

private:
    void load(const char* const file_path);

private:
    String material_name_;
    TexturePtr texture_;
    Color diffuse_;     ///< ディフューズ
    Color ambient_;     ///< アンビエント
    Color specular_;
    uint8_t opacity_;   ///< 透明度
};


}   // namespace t3



#endif  // TRI_MATERIAL_HPP_INCLUDED
