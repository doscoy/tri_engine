
#include "tri_draw_primitive.hpp"
#include "platform/platform_sdk.hpp"
#include "platform/platform.hpp"
#include "geometry/tri_geometry.hpp"


namespace {


void setupOrtho()
{
    float screen_width = glue::getScreenWidth();
    float screen_height = glue::getScreenHeight();

    ogl::matrixMode( GL_PROJECTION );
    ogl::pushMatrix();
    ogl::loadIdentity();
    ogl::ortho( 0, screen_width, screen_height, 0, -1.0f, 1.0f );
    ogl::matrixMode( GL_MODELVIEW );
    ogl::pushMatrix();
    ogl::loadIdentity();
}

}   // unname namespace



namespace t3 {
inline namespace dbg {

void drawPoint(
    const Vec2& pos,
    const Color& color
){
    drawLine( pos, Vec2( pos.x_, pos.y_ + 0.5f ), color );
}

void drawPoint(
    const Vec3& pos,
    const Color& color
) {
    Segment seg1(pos - Vec3(1,0,0), pos + Vec3(1,0,0));
    Segment seg2(pos - Vec3(0,0,1), pos + Vec3(0,0,1));
    
    drawSegment(seg1, color, 0.1f);
    drawSegment(seg2, color, 0.1f);
}

void drawLine(
    const Vec2& start,
    const Vec2& end,
    const Color& color
){
    drawLine( start.x_, start.y_, end.x_, end.y_, color );
}
    
void drawLine(
    float start_x,
    float start_y,
    float end_x,
    float end_y,
    const Color& color
){
    setupOrtho();
    
    
    ogl::begin(GL_LINE_LOOP);

    ogl::color4ub( color.red_, color.green_, color.blue_, color.alpha_ );
    ogl::vertex2f( start_x, start_y );
    ogl::vertex2f( end_x, end_y );

    ogl::end();

}
    
void drawRectangle(
    const Vec2& left_up,
    const Vec2& size,
    const Color& color
){
    setupOrtho();
    
    ogl::begin( GL_QUADS );
    Vec2 end = left_up + size;
    ogl::color4ub( color.red_, color.green_, color.blue_, color.alpha_ );
    ogl::vertex2f( left_up.x_, left_up.y_ );
    ogl::vertex2f( end.x_, left_up.y_ );
    ogl::vertex2f( end.x_, end.y_ );
    ogl::vertex2f( left_up.x_, end.y_ );
    
    ogl::end();
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
    
    ogl::color4ub(color.red_, color.green_, color.blue_, color.alpha_);
	ogl::begin(GL_QUADS);
    ogl::vertex3f(a->x_, a->y_, a->z_);
    ogl::vertex3f(b->x_, b->y_, b->z_);
    ogl::vertex3f(d.x_, d.y_, d.z_);
    ogl::vertex3f(c.x_, c.y_, c.z_);
    ogl::end();

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
    ogl::color4ub(color.red_, color.green_, color.blue_, color.alpha_);
	ogl::begin( GL_QUADS );
    ogl::normal3fv( normal.pointer() );
    ogl::vertex3f( center.x_ - size.x_, center.y_, center.z_ - size.z_ );
    ogl::vertex3f( center.x_ - size.x_, center.y_, center.z_ + size.z_ );
    ogl::vertex3f( center.x_ + size.x_, center.y_, center.z_ + size.z_ );
    ogl::vertex3f( center.x_ + size.x_, center.y_, center.z_ - size.z_ );
    ogl::end();
}


}   // inline namespace dbg
}   // namespace t3
