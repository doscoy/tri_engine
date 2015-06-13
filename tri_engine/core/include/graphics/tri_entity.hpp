/**
    @file tri_entity.hpp
    シーンエンティティ.
*/

#ifndef TRI_ENTITY_HPP_INCLUDED
#define TRI_ENTITY_HPP_INCLUDED

//  include
#include "core_config.hpp"
#include "graphics/tri_render_info.hpp"


TRI_CORE_NS_BEGIN



///
/// エンティティ.
/// シーングラフに登録されるあらゆるものの基底
class Entity {
protected:
    ///
    /// コンストラクタ
    Entity(){};

    ///
    /// デストラクタ
    virtual ~Entity(){};
    
public:
    ///
    /// 描画するものか判定
    virtual bool isRenderable() const {
        return false;
    }
    
    ///
    /// 描画
    virtual void render(const RenderInfo&){}
};


TRI_CORE_NS_END


#endif // TRI_ENTITY_HPP_INCLUDED