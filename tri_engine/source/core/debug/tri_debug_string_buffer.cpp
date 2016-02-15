////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

//  include
#include "core/debug/tri_debug_string_buffer.hpp"
#include "core/graphics/tri_color.hpp"
#include "core/debug/tri_print.hpp"
#include "core/kernel/tri_kernel.hpp"
#include "core/base/tri_director.hpp"
#include "core/base/tri_screen_manager.hpp"


TRI_CORE_NS_BEGIN

///
/// コンストラクタ
DebugStringBuffer::DebugStringBuffer()
{}

///
/// デストラクタ
DebugStringBuffer::~DebugStringBuffer()
{}

///
/// 文字列追加
void DebugStringBuffer::addString(
    const float x,
    const float y,
    const rgba32_t color,
    const int size,
    const char* const str
) {
    
    //  受け取った文字列を一文字づつに分解して保存
    int font_size = size;
    int pitch = font_size;
    int count = 0;
    int start_x = x * font_size;
    int start_y = y * font_size;
    
    // (0, 0)が左端になる座標系
    auto half_size = ScreenManager::instance().virtualScreenSize().half();

    const char* c = str;
    while(*c){
        DebugStringItem character;
        character.x_ = start_x + (pitch * count) - half_size.x_ + 32;
        character.y_ = half_size.y_ - start_y + 32;
        character.size_ = size;
        character.character_ = *c;
        character.color_ = color;
        
        push_back(character);

        ++c;
        ++count;
    }
}

TRI_CORE_NS_END

