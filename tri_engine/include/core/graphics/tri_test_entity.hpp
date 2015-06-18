/**
    @file tri_test_entity.hpp
    テストエンティティ.
*/

#ifndef TRI_TEST_ENTITY_HPP_INCLUDED
#define TRI_TEST_ENTITY_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_entity.hpp"
#include "tri_color.hpp"
#include "core/debug/tri_draw_primitive.hpp"

TRI_CORE_NS_BEGIN


///
/// テスト用オブジェクト
class TestEntity
    : public Entity
{
public:
    ///
    /// 描画
    virtual void render() {
    
        drawPlane(
            Vec3(0,0,0),
            Vec3(0,1,0),
            Vec3(2,2,2),
            color_sample::blue()
        );

    }

    ///
    /// 描画判定
    virtual bool isRenderable() const {
        return true;
    }
};


TRI_CORE_NS_END


#endif // TRI_TEST_ENTITY_HPP_INCLUDED
