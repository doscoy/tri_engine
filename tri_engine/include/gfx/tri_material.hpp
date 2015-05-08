
#ifndef TRI_MATERIAL_HPP_INCLUDED
#define TRI_MATERIAL_HPP_INCLUDED

//  include
#include "tri_color.hpp"

namespace t3 {

///
/// マテリアル
class Material
{
public:

    ///
    /// コンストラクタ
    Material()
        : diffuse_()
        , ambient_()
        , opacity_(255)
    {}
    
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

private:
    Color diffuse_;     ///< ディフューズ
    Color ambient_;     ///< アンビエント
    uint8_t opacity_;   ///< 透明度
};


}   // namespace t3



#endif  // TRI_MATERIAL_HPP_INCLUDED
