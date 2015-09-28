////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/debug/tri_debug_string_buffer.hpp"
#include "core/graphics/tri_color.hpp"
#include "core/debug/tri_print.hpp"
#include "core/kernel/tri_kernel.hpp"
#include "core/base/tri_director.hpp"



TRI_CORE_NS_BEGIN


DebugStringBuffer::DebugStringBuffer()
{}

DebugStringBuffer::~DebugStringBuffer()
{}


void DebugStringBuffer::addString(
    const float x,
    const float y,
    const rgba32_t color,
    const int size,
    const char* const str
){


    
    //  受け取った文字列を一文字づつに分解して保存
    
    int font_size = size;
    int pitch = font_size - 2;
    int count = 0;
    const char* c = str;
    while(*c){
        DebugStringItem character;
        character.x_ = x + (pitch * count);
        character.y_ = y;
        character.size_ = size;
        character.character_ = *c;
        character.color_ = color;
        
        push_back(character);

        ++c;
        ++count;
    }

    
}

TRI_CORE_NS_END

