
#ifndef TRI_DEBUG_SCREEN_LAYER_HPP_INCLUDED
#define TRI_DEBUG_SCREEN_LAYER_HPP_INCLUDED

#include "../gfx/tri_render_layer.hpp"
#include "tri_debug_string_buffer.hpp"


namespace t3 {
inline namespace dbg {

class DebugStringLayer
    : public RenderLayer
{
public:
    DebugStringLayer();
    virtual ~DebugStringLayer();

public:
    void writeString(
        const int x,
        const int y,
        const u_int color,
        const char* const str
    );

private:
    virtual void updateLayer( tick_t tick ) override;
    virtual void drawLayer() override;


private:
    DebugStringBuffer debug_string_buffer_;

};



} // inline namespace dbg
} // namespace t3


#endif // TRI_DEBUG_SCREEN_LAYER_HPP_INCLUDED

