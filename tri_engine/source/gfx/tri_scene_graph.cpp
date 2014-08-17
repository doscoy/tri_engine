
#include "gfx/tri_scene_graph.hpp"
#include "gfx/tri_scene_node.hpp"
#include "dbg/tri_trace.hpp"
#include "gfx/tri_render_system.hpp"
#include "kernel/tri_kernel.hpp"
#include "base/tri_director.hpp"

namespace t3 {
inline namespace gfx {


SceneGraph::SceneGraph()
    : root_()
    , camera_()
    , matrix_stack_()
    , node_map_()
{
    root_ = TransformNode::create("root");
}


SceneGraph::~SceneGraph()
{

}


void SceneGraph::renderScene()
{
    RenderSystem::setCulling(false);
    RenderSystem::setCullingMode(t3::RenderSystem::CullingMode::MODE_BACK);
    RenderSystem::setBlend(false);
    RenderSystem::setDepthTest(true);
    RenderSystem::setDepthWrite(true);
    RenderSystem::setDepthTestMode(t3::RenderSystem::DepthTestMode::MODE_LESS);

    if (root_ && camera_) {
        matrix_stack_.clearStack();
        setupView();
        
        if (root_->preRender(this)) {
            root_->render(this);
            root_->renderChildren(this);
            root_->postRender(this);
        }
    
    }
    
}

void SceneGraph::setupView()
{
    auto& d = t3::Director::instance();
    auto& screen = d.virtualScreenSize();
    
    t3::RenderSystem::setViewport(0, 0, screen.x_, screen.y_);
    t3::Mtx44 projection = t3::Mtx44::getFrustumMatrix(
        -1,
        1,
        -(float)screen.y_ /screen.x_,
        (float)screen.y_/screen.x_,
        0.1f,
        1000.0f
    );
    
    const Mtx44* view_mtx = camera_->viewMatrix();
    Mtx44 view_projection = *view_mtx * projection;
    pushAndSetMatrix(view_projection);
}

void SceneGraph::updateScene(tick_t delta_time)
{

    if (!root_) {
        return;
    }
    
    root_->onUpdate(this, delta_time);
}


void SceneGraph::pushAndSetMatrix(
    const Mtx44& to_world
) {
    matrix_stack_.pushMatrix();
    matrix_stack_.multMatrixLocal(to_world);
}

void SceneGraph::popMatrix()
{
    matrix_stack_.popMatrix();

}


const Mtx44* SceneGraph::topMatrix()
{
    return static_cast<const Mtx44*>(matrix_stack_.topMatrix());
}


SceneNodePtr SceneGraph::findNode(NodeID id)
{
    SceneNodeMap::iterator it = node_map_.find(id);
    
    if (it == node_map_.end()) {
        SceneNodePtr null;
        return null;
    }
    
    return (*it).second;
}


TransformNodePtr SceneGraph::createNode()
{
    return root_->createNode("node");
}









}   // namespace gfx
}   // namespace t3



