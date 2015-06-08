/**
    @file tri_debug_writer.hpp
    デバッグ用画面文字列描画システム.
*/

#ifndef TRI_DEBUG_WRITER_HPP_INCLUDED
#define TRI_DEBUG_WRITER_HPP_INCLUDED


#include "gfx/tri_shader.hpp"
#include "gfx/tri_texture.hpp"

namespace t3 {

class DebugWriter {
public:
    DebugWriter();
    ~DebugWriter();
public:
    enum {
        FONT_PIXEL = 16,
        BUFFER_LENGTH = 256,
    };


    void print(
        const char* str,
        const int x,
        const int y,
        const rgba32_t color,
        const int font_size
    );
    

    void beginPrint(
        const float w,
        const float h
    );
    
    void endPrint();

private:
    void printCore(
        const char c,
        const int x,
        const int y,
        const rgba32_t color,
        const int font_size
    );
    
private:
    float width_;
    float height_;
    TexturePtr font_sheet_;
    ShaderPtr shader_;
};

}   // namespace t3

#endif  // TRI_DEBUG_WRITER_HPP_INCLUDED
