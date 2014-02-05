

#include "tri_render_buffer.hpp"
#include "kernel/platform/platform_sdk.hpp"
#include "tri_frame_buffer.hpp"

namespace t3 {

RenderBuffer::RenderBuffer(
    const int color_format,
    const int width,
    const int height
){
    ogl::genRenderbuffers( 1, &id_ );
    bind();
    ogl::renderbufferStorage( GL_RENDERBUFFER, color_format, width, height );
}


RenderBuffer::~RenderBuffer()
{
    ogl::deleteRenderbuffers( 1, &id_ );
}


void RenderBuffer::bind()
{
    ogl::bindRenderbuffer( GL_RENDERBUFFER, id_ );
}

void RenderBuffer::unbind()
{
    ogl::bindRenderbuffer( GL_RENDERBUFFER, 0 );
}


    
void RenderBuffer::attachFrameBuffer(
    FrameBuffer& frame_buffer,
    int attachment_point
){
    frame_buffer.bind();
    ogl::framebufferRenderbuffer(
        GL_FRAMEBUFFER,
        attachment_point,
        GL_RENDERBUFFER,
        id_
    );
}


}   // namespace t3