
#include "gfx/tri_transform_node.hpp"
#include "gfx/tri_entity.hpp"
#include "dbg/tri_trace.hpp"
#include "gfx/tri_scene_graph.hpp"
#include "kernel/memory/tri_new.hpp"




namespace t3 {
inline namespace gfx {

extern NodeID getNewNodeID();

TransformNode::TransformNode(
    NodeID id,
    std::string name
)   : parent_(nullptr)
    , children_()
    , position_(0, 0, 0)
    , rotation_(0, 0, 0)
    , scale_(1.0f, 1.0f, 1.0f)
    , visible_(true)
    , transform_()
    , calc_request_(true)
    , entity_(nullptr)
    , node_id_(id)
{
}

TransformNode::~TransformNode()
{
}



void TransformNode::onUpdate(
    t3::SceneGraph* scene_graph,
    tick_t delta_time
) {
    SceneNodeList::iterator it = children_.begin();
    SceneNodeList::iterator end = children_.end();
    
    while (it != end) {
        (*it)->onUpdate(scene_graph, delta_time);
        it++;
    }
}


void TransformNode::render(
    SceneGraph* scene_graph
) {
    if (hasEntity()
        && entity_->isRenderable()) {
    
        entity_->render(*scene_graph->topMatrix());
    }
}

const Mtx44* TransformNode::getTransformMatrix() {

    if (calc_request_) {
        calc_request_ = false;
        makeTransformMatrix();
    }

    return &transform_;
}


void TransformNode::makeTransformMatrix()
{
    Mtx44 s;
    s.scale(scale_);
    
    Mtx44 r;
    r.rotate(rotation_);
    
    Mtx44 t;
    t.translate(position_);


    transform_ = s * r * t;
}

void TransformNode::renderChildren(t3::SceneGraph *scene_graph)
{
    SceneNodeList::iterator it = children_.begin();
    SceneNodeList::iterator end = children_.end();
    
    while (it != end) {
        SceneNodePtr node = (*it);
        if (node->preRender(scene_graph)) {
        
            //  prerenderでfalseだったらレンダリングは省略できる
            if (node->isVisible(scene_graph)) {
                node->render(scene_graph);
                
            }
            node->renderChildren(scene_graph);
        }
        node->postRender(scene_graph);
        it++;
    }
}

void TransformNode::detachParent(
    SceneNodePtr kid
) {
    ISceneNode* kid_parent = kid->getParent();
    if (kid_parent) {
        NodeID kid_id = kid->getNodeID();
        kid_parent->removeChild(kid_id);
    }
}

bool TransformNode::addChild(
    SceneNodePtr kid
) {
    if (kid->getParent() == this) {
        return true;
    }
    
    detachParent(kid);
    
    children_.push_back(kid);
    kid->setParent(this);
    
    return true;
}


bool TransformNode::removeChild(
    NodeID id
) {

	for (SceneNodeList::iterator it = children_.begin(); it != children_.end(); ++it) {
	
		if (id == (*it)->getNodeID()) {
			it = children_.erase(it);
			return true;
		}
	}
	return false;

}

bool TransformNode::preRender(
    t3::SceneGraph* scene_graph
) {

    scene_graph->pushAndSetMatrix(*getTransformMatrix());
    
    return true;
}

void TransformNode::postRender(t3::SceneGraph *scene_graph) {
    scene_graph->popMatrix();
}


bool TransformNode::isVisible(t3::SceneGraph *scene_graph) const
{

    // フラスタムによる可視判定を書く

    return true;
}

TransformNodePtr TransformNode::createNode(
    std::string name
) {
    TransformNodePtr new_node = create(name);
    addChild(new_node);
    return new_node;
}

TransformNodePtr TransformNode::create(
    std::string name
) {
    TransformNodePtr new_node(T3_SYS_NEW TransformNode(getNewNodeID(), name));
    
    return new_node;
}

}   // namespace theater
}   // namespace t3


