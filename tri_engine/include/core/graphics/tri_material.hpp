/**
    @file tri_material.hpp
    マテリアル.
*/

#ifndef TRI_MATERIAL_HPP_INCLUDED
#define TRI_MATERIAL_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_color.hpp"
#include "tri_texture.hpp"



TRI_CORE_NS_BEGIN


class Material;
using MaterialPtr = SharedPtr<Material>;


///
/// マテリアル
class Material {
protected:
    ///
    /// コンストラクタ
    Material()
        : diffuse_(255, 0, 0)
        , ambient_(128, 0, 0)
        , specular_(0, 255, 0)
        , opacity_(255)
    {}


public:

    ///
    /// デストラクタ
    ~Material()
    {}



    ///
    /// Diffuse 設定
    void diffuse(
        const Color& color
    ) {
        diffuse_ = color;
    }

    ///
    /// Diffuse 取得
    const auto& diffuse() const {
        return diffuse_;
    }

    ///
    /// Ambient 設定
    void ambient(
        const Color& color
    ) {
        ambient_ = color;
    }

    ///
    /// Ambient 取得
    const auto& ambient() const {
        return ambient_;
    }
    
    ///
    /// Specular 設定
    void specular(
        const Color& color
    ) {
        specular_ = color;
    }

    ///
    /// Specular 取得
    const auto& specular() const {
        return specular_;
    }
    
    ///
    /// 透明度を持っているか
    bool hasAlpha() const {
        return opacity_ < 255;
    }
    
    ///
    /// 透明度取得
    uint8_t opacity() const {
        return opacity_;
    }
    
    ///
    /// 透明度設定
    void opacity(int a) {
        opacity_ = a;
    }
    
    ///
    /// 使用
    void use() {
    
    }

    ///
    /// マテリアル名を取得
    auto& name() {
        return material_name_;
    }

    ///
    /// マテリアル名を設定
    void name(const String& name) {
        material_name_ = name;
    }
    
    ///
    /// テクスチャを取得
    const auto& texture() const {
        return texture_;
    }

    ///
    /// テクスチャを設定
    void texture(TexturePtr t) {
        texture_ = t;
    }

public:
    static MaterialPtr create();


private:
    String material_name_;
    TexturePtr texture_;
    Color diffuse_;     ///< ディフューズ
    Color ambient_;     ///< アンビエント
    Color specular_;
    uint8_t opacity_;   ///< 透明度
};


TRI_CORE_NS_END



#endif  // TRI_MATERIAL_HPP_INCLUDED
