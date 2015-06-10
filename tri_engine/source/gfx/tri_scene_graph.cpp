
#include "gfx/tri_scene_graph.hpp"
#include "gfx/tri_scene_node.hpp"
#include "dbg/tri_trace.hpp"

#include "kernel/tri_kernel.hpp"
#include "base/tri_director.hpp"

namespace t3 {


SceneGraph::SceneGraph()
    : root_(TransformNode::create("root"))
    , camera_()
    , projector_(Projector::create())
    , matrix_stack_()
    , node_map_()
{
    auto& d = t3::Director::instance();
    auto& screen = d.deviceScreenSize();
    
    
}


SceneGraph::~SceneGraph()
{

}


void SceneGraph::renderScene()
{
    cross::RenderSystem::setCulling(true);
    cross::RenderSystem::setCullingMode(cross::RenderSystem::CullingMode::MODE_BACK);
    cross::RenderSystem::setBlend(false);
    cross::RenderSystem::setDepthTest(true);
    cross::RenderSystem::setDepthWrite(true);
    cross::RenderSystem::setDepthTestMode(cross::RenderSystem::DepthTestMode::MODE_LESS);

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
    auto& screen = d.deviceScreenSize();
    
    cross::RenderSystem::setViewport(
        0, 
        0, 
        static_cast<int>(screen.x_), 
        static_cast<int>(screen.y_)
	);
    
    auto use_cam = camera_;
    if (render_mode_ == RenderInfo::SHADOW) {
        use_cam = light_camera_;
    }
    const Mtx44& view_mtx = use_cam->viewMatrix();
    auto view_projection = view_mtx * projector_->projectionMatrix();
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



}   // namespace t3



