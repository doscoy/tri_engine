////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "core/graphics/tri_material.hpp"

TRI_CORE_NS_BEGIN

MaterialPtr Material::create() {
    MaterialPtr p;
    p.reset(T3_NEW Material());
    return p;
}


TRI_CORE_NS_END

