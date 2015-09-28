////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_dae_loader.hpp
    .dae loader.
*/

#ifndef TRI_DAE_LOADER_HPP_INCLUDED
#define TRI_DAE_LOADER_HPP_INCLUDED

//  include

#include "tri_submesh_data.hpp"



TRI_CORE_NS_BEGIN

///
/// .ade loader
class DaeLoader {
public:
    static SubMeshesDataPtr load(
        const char* const path
    );
};


TRI_CORE_NS_END



#endif  // TRI_DAE_LOADER_HPP_INCLUDED
