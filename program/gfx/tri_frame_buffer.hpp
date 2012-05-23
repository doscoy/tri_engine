
#ifndef TRI_FRAMEBUFFER_HPP_INCLUDED
#define TRI_FRAMEBUFFER_HPP_INCLUDED

#include "tri_develop_base.hpp"


namespace t3 {


class RenderBuffer;

class FrameBuffer
{
public:
    FrameBuffer();
    ~FrameBuffer();
    
public:
    void bind() const;
    void unbind() const;
    u_int getID() const {
        return id_;
    }
private:
    u_int id_;
    
};


}   // namespace t3

#endif // TRI_FRAMEBUFFER_HPP_INCLUDED