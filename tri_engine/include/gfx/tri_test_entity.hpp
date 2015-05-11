/**
    @file tri_test_entity.hpp
    テストエンティティ.
*/

#ifndef TRI_TEST_ENTITY_HPP_INCLUDED
#define TRI_TEST_ENTITY_HPP_INCLUDED

//  include
#include "tri_entity.hpp"
#include "tri_color.hpp"


namespace t3 {

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
            t3::Vec3(0,0,0),
            t3::Vec3(0,1,0),
            t3::Vec3(2,2,2),
            t3::color_sample::blue()
        );

    }

    ///
    /// 描画判定
    virtual bool isRenderable() const {
        return true;
    }
};


}   // namespace t3


#endif // TRI_TEST_ENTITY_HPP_INCLUDED
