#include "tri_scene_node.hpp"


namespace t3 {
inline namespace gfx {


node_id_t getNewNodeID()
{
    static node_id_t new_id = 0;
    ++new_id;
    return new_id;
}

}   // namespace gfx
}   // namespace t3
