#include "gfx/tri_scene_node.hpp"


namespace t3 {
inline namespace gfx {


NodeID getNewNodeID()
{
    static NodeID new_id = 0;
    ++new_id;
    return new_id;
}

}   // namespace gfx
}   // namespace t3
