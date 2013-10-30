
#include "tri_scene_node_properties.hpp"

namespace t3 {
inline namespace gfx {



SceneNodeProperties::SceneNodeProperties(
    actor_id_t id,
    std::string name,
    RenderPass render_pass,
    AlphaType alpha_type
)   : actor_id_(id)
    , name_(name)
    , to_world_()
    , from_world_()
    , radius_(0)
    , render_pass_(render_pass)
    , material_()
    , alpha_type_(ALPHA_OPAQUE)
{

}


void SceneNodeProperties::getTransformMatrix(
    Mtx4* to_world,
    Mtx4* from_world
) const {
    if (to_world) {
        *to_world = to_world_;
    }
    
    if (from_world) {
        *from_world = from_world_;
    }
    
}
    
    



}   // namespace gfx
}   // namespace t3

