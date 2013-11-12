#ifndef TRI_RENDER_BUFFER_HPP_INCLUDED
#define TRI_RENDER_BUFFER_HPP_INCLUDED

#include <cstdint>

namespace t3 {
    
class FrameBuffer;
class RenderBuffer
{
public:
    RenderBuffer(
        const int color_format,
        const int width,
        const int height
    );
    ~RenderBuffer();

public:
    void bind();
    
    void unbind();
    
    uint32_t getID() const {
        return id_;
    }
    
    void attachFrameBuffer(
        FrameBuffer& frame_buffer,
        int attachment_point
    );
    
private:
    uint32_t id_;
};

}   // namespace t3

#endif // TRI_RENDER_BUFFER_HPP_INCLUDED