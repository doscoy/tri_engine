
#ifndef TRI_FRAMEBUFFER_HPP_INCLUDED
#define TRI_FRAMEBUFFER_HPP_INCLUDED

#include <cstdint>


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
    uint32_t getID() const {
        return id_;
    }
private:
    uint32_t id_;
    
};


}   // namespace t3

#endif // TRI_FRAMEBUFFER_HPP_INCLUDED