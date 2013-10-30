//
//  tri_material.hpp
//  dev_t3
//
//  Created by 哲郎 可児 on 12/05/24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef dev_t3_tri_material_hpp
#define dev_t3_tri_material_hpp


#include "tri_color.hpp"

namespace t3 {
inline namespace gfx {

class Material
{
public:
    bool hasAlpha() const {
        return opacity_ <= 255;
    }
    
    u_char getOpacity() const {
        return opacity_;
    }
    
    void setOpacity(int opacity) {
        opacity_ = opacity;
    }
    
    void use() {
    
    }

private:
    Color diffuse_;
    Color ambient_;
    u_char opacity_;

};


}   // namespace gfx
}   // namespace t3



#endif
