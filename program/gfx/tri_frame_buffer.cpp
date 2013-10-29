#include "tri_frame_buffer.hpp"
#include "platform_sdk.hpp"
#include "tri_render_buffer.hpp"
#include <iostream>

namespace  {

bool checkFramebufferStatus()
{
    // check FBO status
    GLenum status = ogl::checkFramebufferStatus(GL_FRAMEBUFFER_EXT);
    switch(status)
    {
        case GL_FRAMEBUFFER_COMPLETE_EXT:
            std::cout << "Framebuffer complete." << std::endl;
            return true;
        
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
            std::cout << "[ERROR] Framebuffer incomplete: Attachment is NOT complete." << std::endl;
            return false;
        
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
            std::cout << "[ERROR] Framebuffer incomplete: No image is attached to FBO." << std::endl;
            return false;
        
        case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
            std::cout << "[ERROR] Framebuffer incomplete: Attached images have different dimensions." << std::endl;
            return false;
        
        case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
            std::cout << "[ERROR] Framebuffer incomplete: Color attached images have different internal formats." << std::endl;
            return false;
        
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
            std::cout << "[ERROR] Framebuffer incomplete: Draw buffer." << std::endl;
            return false;
        
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
            std::cout << "[ERROR] Framebuffer incomplete: Read buffer." << std::endl;
            return false;
        
        case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
            std::cout << "[ERROR] Unsupported by FBO implementation." << std::endl;
            return false;
        
        default:
            std::cout << "[ERROR] Unknow error." << std::endl;
    }
    return false;
}


}   // unname namespace


namespace t3 {


FrameBuffer::FrameBuffer()
{
    ogl::genFramebuffers( 1, &id_ );    // FBO作成 
    checkFramebufferStatus();
}


FrameBuffer::~FrameBuffer()
{
    ogl::deleteFramebuffers( 1, &id_ ); // FBO削除
}


void FrameBuffer::bind() const
{
    ogl::bindFramebuffer( GL_FRAMEBUFFER, id_ );
}

void FrameBuffer::unbind() const
{
    ogl::bindFramebuffer( GL_FRAMEBUFFER, 0 );
}

}   // namespace t3
















