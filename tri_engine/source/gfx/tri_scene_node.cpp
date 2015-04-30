#include "gfx/tri_scene_node.hpp"


namespace t3 {


NodeID getNewNodeID()
{
    static NodeID new_id = 0;
    ++new_id;
    return new_id;
}


}   // namespace t3
