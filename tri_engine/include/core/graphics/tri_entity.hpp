////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_entity.hpp
    シーンエンティティ.
*/

#ifndef TRI_ENTITY_HPP_INCLUDED
#define TRI_ENTITY_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/graphics/tri_render_info.hpp"


TRI_CORE_NS_BEGIN



///
/// エンティティ.
/// シーングラフに登録されるあらゆるものの基底
class Entity {
protected:
    ///
    /// コンストラクタ
    Entity(){};

    
public:
    ///
    /// デストラクタ
    virtual ~Entity(){};

    ///
    /// 描画するものか判定
    virtual bool isRenderable() const {
        return false;
    }
    
    ///
    /// 描画
    virtual void render(const RenderInfo&){}

};
using EntityPtr = SharedPtr<Entity>;

TRI_CORE_NS_END


#endif // TRI_ENTITY_HPP_INCLUDED