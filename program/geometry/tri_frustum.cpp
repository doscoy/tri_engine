//
//  tri_frustum.cpp
//  dev_t3
//
//  Created by 哲郎 可児 on 12/06/13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "tri_frustum.hpp"

namespace t3 {
inline namespace geometry {

Frustum::Frustum()
{

}


Frustum::~Frustum()
{

}


bool Frustum::isInside(
    const Vec3 &pos
) const {
    return true;
}

}   // namespace geometry
}   // namespace t3


