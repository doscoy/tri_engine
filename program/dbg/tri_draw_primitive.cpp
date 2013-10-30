
#include "tri_draw_primitive.hpp"
#include "platform_sdk.hpp"
#include "platform.hpp"



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
    drawLine( pos, Vec2( pos.x, pos.y+0.5f ), color );
}

void drawLine(
    const Vec2& start,
    const Vec2& end,
    const Color& color
){
    drawLine( start.x, start.y, end.x, end.y, color );
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
    ogl::vertex2f( left_up.x, left_up.y );
    ogl::vertex2f( end.x, left_up.y );
    ogl::vertex2f( end.x, end.y );
    ogl::vertex2f( left_up.x, end.y );
    
    ogl::end();
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
    ogl::vertex3f( center.x - size.x, center.y, center.z - size.z );
    ogl::vertex3f( center.x - size.x, center.y, center.z + size.z );
    ogl::vertex3f( center.x + size.x, center.y, center.z + size.z );
    ogl::vertex3f( center.x + size.x, center.y, center.z - size.z );   
    ogl::end();
}


}   // inline namespace dbg
}   // namespace t3
