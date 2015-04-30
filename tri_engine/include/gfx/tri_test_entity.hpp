
#ifndef tri_sandbox_osx_tri_test_entity_hpp
#define tri_sandbox_osx_tri_test_entity_hpp

//#include "tri_renderabl.hpp"
#include "tri_entity.hpp"
#include "tri_color.hpp"


namespace t3 {


class TestEntity
    : public Entity
{
public:
    virtual void render() {
    
        drawPlane(
            t3::Vec3(0,0,0),
            t3::Vec3(0,1,0),
            t3::Vec3(2,2,2),
            t3::Color::BLUE
        );

    }

    virtual bool isRenderable() const {
        return true;
    }
};


}   // namespace t3


#endif
