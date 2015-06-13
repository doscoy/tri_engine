#include "graphics/tri_scene_node.hpp"


TRI_CORE_NS_BEGIN



NodeID getNewNodeID()
{
    static NodeID new_id = 0;
    ++new_id;
    return new_id;
}


TRI_CORE_NS_END
