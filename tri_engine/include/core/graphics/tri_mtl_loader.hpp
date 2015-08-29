/**
    @file tri_material.hpp
    mtlファイルローダ.
*/

#ifndef TRI_MTL_LOADER_HPP_INCLUDED
#define TRI_MTL_LOADER_HPP_INCLUDED

//  include
#include "tri_material.hpp"



TRI_CORE_NS_BEGIN

///
/// マテリアル
struct MtlLoader {
    static MaterialPtr load(
        const char* const path  
    );
};

TRI_CORE_NS_END



#endif  // TRI_MATERIAL_HPP_INCLUDED
