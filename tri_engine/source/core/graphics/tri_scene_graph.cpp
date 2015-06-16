
#include "core/graphics/tri_scene_graph.hpp"
#include "core/graphics/tri_scene_node.hpp"
#include "core/debug/tri_trace.hpp"

#include "core/kernel/tri_kernel.hpp"
#include "core/base/tri_director.hpp"

namespace t3 {


SceneGraph::SceneGraph()
    : root_(TransformNode::create("root"))
    , camera_()
    , shadow_camera_()
    , projector_(Projector::create())
    , shadow_projector_(Projector::create())
    , matrix_stack_()
    , node_map_()
    , shadow_texture_()
    , render_mode_()
{}


SceneGraph::~SceneGraph()
{

}


void SceneGraph::renderScene(
    RenderInfo::Mode mode
) {
    render_mode_ = mode;
    

    if (mode == RenderInfo::SHADOW) {
        //  影テクスチャを作る時はフロントフェースカリング
        cross::RenderSystem::setCullingMode(cross::RenderSystem::CullingMode::MODE_FRONT);
    } else {
        //  通常描画は強制カリング
        cross::RenderSystem::setCullingMode(cross::RenderSystem::CullingMode::MODE_BACK);
    }

    //  基本描画設定
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
    auto use_cam = camera_;
    auto use_projector = projector_;
    if (render_mode_ == RenderInfo::SHADOW) {
        use_cam = shadow_camera_;
        use_projector = shadow_projector_;
    }
    const Mtx44& view_mtx = use_cam->viewMatrix();
    const Mtx44& proj_mtx = use_projector->projectionMatrix();
    auto view_projection = proj_mtx * view_mtx;
    pushAndSetMatrix(view_projection);
    
    cross::RenderSystem::setViewport(
        0, 
        0, 
        static_cast<int>(use_projector->screenSize().x_),
        static_cast<int>(use_projector->screenSize().y_)
	);
 
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



