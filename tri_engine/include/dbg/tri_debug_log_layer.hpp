//
//  tri_debug_log_layer.hpp
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/11/01.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//

#ifndef tri_sandbox_osx_tri_debug_log_layer_hpp
#define tri_sandbox_osx_tri_debug_log_layer_hpp

#include "tri_debug_string_layer.hpp"
#include "tri_debug_log_buffer.hpp"


namespace t3 {
inline namespace dbg {


class DebugLogLayer
    : public DebugStringLayer
{
public:
    DebugLogLayer(const char* const name = "DISPLAY LOG");
    virtual ~DebugLogLayer();

public:
    void writeString(
        const char* const str
    );
    
    void slideUp();
    void slideDown();
    
    
protected:
    void updateLayer( tick_t delta_time ) override;
    void drawLayer() override;
    
    int getLogShowLineIndex() const;

protected:
    DebugLogBuffer debug_log_buffer_;
    int log_show_offset_;
};

}   // namespace dbg
}   // namespace t3



#endif
