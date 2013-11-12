
#include "tri_scene_graph.hpp"
#include "tri_root_node.hpp"
#include "tri_camera_node.hpp"
#include "tri_test_object_node.hpp"
#include "../dbg/tri_trace.hpp"
#include "../kernel/tri_kernel.hpp"

namespace t3 {
inline namespace gfx {

node_id_t SceneGraph::next_actor_id_ = 1;

SceneGraph::SceneGraph()
    : root_()
    , camera_node_()
    , matrix_stack_()
    , alpha_scene_nodes_()
    , node_map_()
{
    root_ = RootNode::create(issueNodeID());
}


SceneGraph::~SceneGraph()
{

}


void SceneGraph::renderScene()
{

    if (root_ && camera_node_) {
        matrix_stack_.clearStack();
        camera_node_->setViewTransform(this);
        
        if (root_->preRender(this)) {
            root_->render(this);
            root_->renderChildren(this);
            root_->postRender(this);
        }
    
    }
    
    renderAlphaPass();
}


void SceneGraph::restoreScene()
{
    if (!root_) {
        return;
    }
    
    root_->onRestore(this);

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


std::shared_ptr<ISceneNode> SceneGraph::findActor(node_id_t id)
{
    SceneActorMap::iterator it = node_map_.find(id);
    
    if (it == node_map_.end()) {
        std::shared_ptr<ISceneNode> null;
        return null;
    }
    
    return (*it).second;
}



void SceneGraph::renderAlphaPass()
{
    //  現在のワールド変換行列とz write設定を保存
    
    //  アルファ描画用設定
    
    //  アルファノードのソート
    alpha_scene_nodes_.sort();
    
    while (!alpha_scene_nodes_.empty()) {
        AlphaSceneNodes::reverse_iterator it = alpha_scene_nodes_.rbegin();
        
        //  ワールド変換行列設定
        
        //
        (*it)->node_->render(this);
        
        delete (*it);
        alpha_scene_nodes_.pop_back();
  
    }


    //  最初に保存した行列と設定をもとに戻す
}


std::shared_ptr<CameraNode> SceneGraph::createCamera()
{
    std::shared_ptr<CameraNode> new_node = CameraNode::create(issueNodeID());
    root_->addChild(new_node);
    return new_node;
}

std::shared_ptr<TestObjectNode> SceneGraph::createTestObject()
{
    std::shared_ptr<TestObjectNode> new_node =TestObjectNode::create(issueNodeID());
    root_->addChild(new_node);
    return new_node;

}






}   // namespace gfx
}   // namespace t3



