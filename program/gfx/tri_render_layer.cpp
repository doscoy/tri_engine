

#include "tri_render_layer.hpp"
#include <OpenGL/gl.h>



namespace t3{

RenderLayer::RenderLayer()
{

}

RenderLayer::~RenderLayer()
{

}

void RenderLayer::render()
{
    glBegin( GL_QUADS );
    
    glTexCoord2d( 0, 1 );
    glVertex3d(-1, -1, 0);
    glTexCoord2d(1, 1);
    glVertex3d(1, -1, 0);
    glTexCoord2d(1, 0);
    glVertex3d(1, 1, 0);
    glTexCoord2d(0, 0);
    glVertex3d(-0.5, 1, 0);
    
    glEnd();

}

}   // namespace t3

