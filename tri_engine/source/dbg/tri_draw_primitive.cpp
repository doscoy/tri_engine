
#include "tri_draw_primitive.hpp"
#include "platform/platform_sdk.hpp"
#include "platform/platform.hpp"
#include "geometry/tri_geometry.hpp"
#include "base/tri_game_system.hpp"
#include "gfx/tri_render_system.hpp"



namespace {


void setupOrtho()
{
    t3::GameSystem& gs = t3::GameSystem::getInstance();

    float screen_width = gs.getScreenSize().x_;
    float screen_height = gs.getScreenSize().y_;
 
    t3::Mtx4 projection;
    projection.ortho(0, screen_width, screen_height, 0, -1, 1);
    t3::RenderSystem::setProjectionMatrix(projection);

    t3::Mtx4 world;
    world.identity();
    t3::RenderSystem::setWorldTransformMatrix(world);
    
}

}   // unname namespace



namespace t3 {
inline namespace dbg {

void drawPoint(
    const Vec3& pos,
    const Color& color
) {
    Segment seg1(pos - Vec3(1,0,0), pos + Vec3(1,0,0));
    Segment seg2(pos - Vec3(0,0,1), pos + Vec3(0,0,1));
    
    drawSegment(seg1, color, 0.1f);
    drawSegment(seg2, color, 0.1f);
}

    
void drawRectangle(
    const Vec2& left_up,
    const Vec2& size,
    const Color& color
){
    setupOrtho();
    RenderSystem::drawQuad(
        Vec3(left_up.x_, left_up.y_, 0),
        Vec3(left_up.x_ + size.x_, left_up.y_, 0),
        Vec3(left_up.x_ + size.x_, left_up.y_ + size.y_, 0),
        Vec3(left_up.x_, left_up.y_ + size.y_, 0),
        color
    );
}

void drawSegment(
    const Segment& Segment,
    const Color& color,
    const float width
) {
    
    const Vec3* a = Segment.getPointA();
    const Vec3* b = Segment.getPointB();
    
    Vec3 ba = *b - *a;
    Vec3 cross(0,1,0);
    if (isZeroFloat(ba.x_) && isZeroFloat(ba.z_)) {
        //  完全に垂直
        cross = Vec3(1,0,0);
    }

    Vec3 offset = ba.crossProduct(cross);
    offset.normalize();
    
    offset *= width;
    Vec3 c = *a + offset;
    Vec3 d = *b + offset;
    
    
    
    RenderSystem::drawQuad(
        *a,
        *b,
        c,
        d,
        color
    );
    
}

void drawAxis(
    const Vec3& pos
) {
        t3::Segment seg1(
        t3::Vec3(0, 3, 0),
        t3::Vec3(0, 0, 0)
    );

    t3::Segment seg2(
        t3::Vec3(0, 0, 3),
        t3::Vec3(0, 0, 0)
    );

    t3::Segment seg3(
        t3::Vec3(3, 0, 0),
        t3::Vec3(0, 0, 0)
    );
    
    t3::drawSegment(seg1, t3::Color::red(), 3.1f);
    t3::drawSegment(seg2, t3::Color::blue(), 3.1f);
    t3::drawSegment(seg3, t3::Color::green(), 3.1f);
}

void drawPlane(
    const Vec3& center,
    const Vec3& normal,
    const Vec3& size,
    const Color& color
){

}


}   // inline namespace dbg
}   // namespace t3
