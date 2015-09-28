////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_obj_loader.hpp
    .obj ローダ.
*/

#ifndef TRI_OBJ_LOADER_HPP_INCLUDED
#define TRI_OBJ_LOADER_HPP_INCLUDED

//  include
#include "tri_submesh_data.hpp"


TRI_CORE_NS_BEGIN



///
/// .obj ローダ
class ObjLoader {
public:
    static SubMeshDataPtr load(
        const char* const path  
    );
};


TRI_CORE_NS_END



#endif  // TRI_OBJ_LOADER_HPP_INCLUDED
