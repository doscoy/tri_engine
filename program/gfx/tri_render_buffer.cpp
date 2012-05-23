

#include "tri_render_buffer.hpp"
#include "platform_sdk.hpp"
#include "tri_frame_buffer.hpp"

namespace t3 {

RenderBuffer::RenderBuffer(
    const int color_format,
    const int width,
    const int height
){
    glGenRenderbuffers( 1, &id_ );
    bind();
    glRenderbufferStorage( GL_RENDERBUFFER, color_format, width, height );
}


RenderBuffer::~RenderBuffer()
{
    glDeleteRenderbuffers( 1, &id_ );
}


void RenderBuffer::bind()
{
    glBindRenderbuffer( GL_RENDERBUFFER, id_ );
}

void RenderBuffer::unbind()
{
    glBindRenderbuffer( GL_RENDERBUFFER, 0 );
}


    
void RenderBuffer::attachFrameBuffer(
    FrameBuffer& frame_buffer,
    int attachment_point
){
    frame_buffer.bind();
    glFramebufferRenderbuffer( GL_FRAMEBUFFER, attachment_point, GL_RENDERBUFFER, id_ );
}


}   // namespace t3