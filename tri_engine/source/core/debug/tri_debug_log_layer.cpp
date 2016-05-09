////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/debug/tri_debug_log_layer.hpp"

TRI_CORE_NS_BEGIN



DebugLogLayer::DebugLogLayer(
    const String& name,
    const LayerBase::Priority priority
)   : DebugStringLayer(name, priority)
    , buffer_()
    , log_show_offset_(0)
{

}


DebugLogLayer::~DebugLogLayer()
{

}


void DebugLogLayer::slideUp() {
    log_show_offset_ -= 1;
}


void DebugLogLayer::slideDown() {
    log_show_offset_ += 1;
}


void DebugLogLayer::updateLayer(const FrameInfo& frame_info) {
    //  ログの内容を描画する
    auto buffer_size = buffer_.size();
    for (int i = 0; i < buffer_size; ++i) {
        const char* str = buffer_.at(i);
        addString(
            static_cast<float>(0), 
            static_cast<float>(i), 
            t3::color_sample::white().rgba32(), 
            10, 
            str
        );
    }
    
    
    //
    DebugStringLayer::updateLayer(frame_info);
}




TRI_CORE_NS_END

