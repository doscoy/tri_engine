
#include "tri_scene_graph.hpp"
#include "tri_scene_node.hpp"
#include "../dbg/tri_trace.hpp"
#include "../kernel/tri_kernel.hpp"
#include "../base/tri_game_system.hpp"

namespace t3 {
inline namespace gfx {


SceneGraph::SceneGraph()
    : root_()
    , camera_()
    , matrix_stack_()
    , node_map_()
{
    root_ = TransformNode::create();
}


SceneGraph::~SceneGraph()
{

}


void SceneGraph::renderScene()
{

    if (root_ && camera_) {
        matrix_stack_.clearStack();
        setupView();
        
        if (root_->preRender(this)) {
            root_->render(this);
            root_->renderChildren(this);
            root_->postRender(this);
        }
    
    }
    
//    renderAlphaPass();
}

void SceneGraph::setupView()
{
    const t3::GameSystem& game_sys = t3::GameSystem::getInstance();
    const t3::Vec2& screen = game_sys.getScreenSize();
    

    ogl::viewport(
        0,
        0,
        screen.x_,
        screen.y_
    );  //ビューポートの設定
    
    ogl::matrixMode(
        GL_PROJECTION
    );
    t3::Mtx4 projection;
    projection.frustum(
        -1,
        1,
        -(float)screen.y_ /screen.x_,
        (float)screen.y_/screen.x_,
        1,
        100
    );
    ogl::loadMatrixf( projection.pointer() );
  
    const Mtx4* view_mtx = camera_->getViewMatrix();
    pushAndSetMatrix(*view_mtx);


}

void SceneGraph::updateScene(tick_t tick)
{

    if (!root_) {
        return;
    }
    
    root_->onUpdate(this, tick);
}


void SceneGraph::pushAndSetMatrix(
    const Mtx4& to_world
) {
    matrix_stack_.pushMatrix();
    matrix_stack_.multMatrixLocal(to_world);
    
    //  変換行列をmatrix_stack.getTopで設定する
    const Mtx4* world = matrix_stack_.getTopMatrix();
    
    ogl::matrixMode(GL_MODELVIEW);
    ogl::loadMatrixf(world->pointer());
}

void SceneGraph::popMatrix()
{
    matrix_stack_.popMatrix();

    //  変換行列をmatrix_stack.getTopで設定する
}


const Mtx4* SceneGraph::getTopMatrix()
{
    return static_cast<const Mtx4*>(matrix_stack_.getTopMatrix());
}


std::shared_ptr<ISceneNode> SceneGraph::findNode(node_id_t id)
{
    SceneNodeMap::iterator it = node_map_.find(id);
    
    if (it == node_map_.end()) {
        std::shared_ptr<ISceneNode> null;
        return null;
    }
    
    return (*it).second;
}


std::shared_ptr<TransformNode> SceneGraph::createNode()
{
    return root_->createNode();
}









}   // namespace gfx
}   // namespace t3



