
#include "tri_draw_primitive.hpp"
#include "platform_sdk.hpp"
#include "platform.hpp"



namespace {


void setupOrtho()
{
    float screen_width = glue::getScreenWidth();
    float screen_height = glue::getScreenHeight();

    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
    glLoadIdentity();
    glOrtho( 0, screen_width, screen_height, 0, -1.0f, 1.0f );
    glMatrixMode( GL_MODELVIEW );
    glPushMatrix();
    glLoadIdentity();
}

}   // unname namespace



namespace t3 {
inline namespace dbg {

void drawPoint(
    const vec2_t& pos,
    const color_t& color
){
    drawLine( pos, vec2_t( pos.x, pos.y+0.5f ), color );
}

void drawLine(
    const vec2_t& start,
    const vec2_t& end,
    const color_t& color
){
    drawLine( start.x, start.y, end.x, end.y, color );
}
    
void drawLine(
    float start_x,
    float start_y,
    float end_x,
    float end_y,
    const color_t& color
){
    setupOrtho();
    
    
    glBegin(GL_LINE_LOOP);

    glColor4ub( color.r, color.g, color.b, color.a );
    glVertex2f( start_x, start_y );
    glVertex2f( end_x, end_y );

    glEnd();

}
    
void drawRectangle(
    const vec2_t& left_up,
    const vec2_t& size,
    const color_t& color
){
    setupOrtho();
    
    glBegin( GL_QUADS );
    vec2_t end = left_up + size;
    glColor4ub( color.r, color.g, color.b, color.a );
    glVertex2f( left_up.x, left_up.y );
    glVertex2f( end.x, left_up.y );
    glVertex2f( end.x, end.y );
    glVertex2f( left_up.x, end.y );
    
    glEnd();
}


void drawPlane(
    const vec3_t& center,
    const vec3_t& normal,
    const vec3_t& size,
    const color_t& color
){
    glColor4ub(color.r, color.g, color.b, color.a);
	glBegin( GL_QUADS );
    glNormal3fv( normal.pointer() );
    glVertex3f( center.x - size.x, center.y, center.z - size.z );
    glVertex3f( center.x - size.x, center.y, center.z + size.z );
    glVertex3f( center.x + size.x, center.y, center.z + size.z );
    glVertex3f( center.x + size.x, center.y, center.z - size.z );   
    glEnd();    
}


}   // inline namespace dbg
}   // namespace t3
