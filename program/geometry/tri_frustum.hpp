//
//  tri_frustum.hpp
//  dev_t3
//
//  Created by 哲郎 可児 on 12/06/13.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef dev_t3_tri_frustum_hpp
#define dev_t3_tri_frustum_hpp


#include "../math/tri_vec3.hpp"
#include "tri_plane.hpp"

namespace t3 {
inline namespace geometry {



class Frustum
{
public:
    Frustum();
    ~Frustum();

public:
    bool isInside(
        const Vec3& pos
    ) const;
};


}   // namespace geometry
}   // namespace t3


#endif
