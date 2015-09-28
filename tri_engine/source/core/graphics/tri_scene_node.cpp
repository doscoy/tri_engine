////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
#include "core/graphics/tri_scene_node.hpp"

TRI_CORE_NS_BEGIN

NodeID getNewNodeID()
{
    static NodeID new_id = 0;
    ++new_id;
    return new_id;
}


TRI_CORE_NS_END
