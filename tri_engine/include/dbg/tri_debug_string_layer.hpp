
#ifndef TRI_DEBUG_SCREEN_LAYER_HPP_INCLUDED
#define TRI_DEBUG_SCREEN_LAYER_HPP_INCLUDED

#include "../gfx/tri_render_layer.hpp"
#include "tri_debug_string_buffer.hpp"
#include "../gfx/tri_color.hpp"

namespace t3 {


class DebugStringLayer
    : public RenderLayer
{
public:
    DebugStringLayer(const char* const name = "DEBUG SCREEN");
    virtual ~DebugStringLayer();

public:
    void writeString(
        const int x,
        const int y,
        const uint32_t color,
        const int size,
        const char* const str
    );

protected:
    void updateLayer(tick_t delta_time) override;
    void drawLayer() override;


protected:
    DebugStringBuffer debug_string_buffer_;

};



} // namespace t3


#endif // TRI_DEBUG_SCREEN_LAYER_HPP_INCLUDED

