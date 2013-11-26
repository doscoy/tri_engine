
#include "tri_transform_node.hpp"
#include "tri_entity.hpp"
#include "../dbg/tri_trace.hpp"
#include "tri_scene_graph.hpp"



namespace t3 {
inline namespace gfx {



TransformNode::TransformNode(
    node_id_t id,
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
    tick_t tick
) {
    SceneNodeList::iterator it = children_.begin();
    SceneNodeList::iterator end = children_.end();
    
    while (it != end) {
        (*it)->onUpdate(scene_graph, tick);
        it++;
    }
}


void TransformNode::render(
    SceneGraph* scene_graph
) {
    if (hasEntity()) {
        if (entity_->isRenderable()) {
            entity_->render();
        }
    }
}

const Mtx4* TransformNode::getTransformMatrix() {

    if (calc_request_) {
        calc_request_ = false;
        makeTransformMatrix();
    }

    return &transform_;
}


void TransformNode::makeTransformMatrix()
{
    Mtx4 s;
    s.scale(scale_);
    
    Mtx4 r;
    r.rotate(rotation_);
    
    Mtx4 t;
    t.translate(position_);


    transform_ = s * r * t;
}

void TransformNode::renderChildren(t3::SceneGraph *scene_graph)
{
    SceneNodeList::iterator it = children_.begin();
    SceneNodeList::iterator end = children_.end();
    
    while (it != end) {
        std::shared_ptr<ISceneNode> node = (*it);
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
    std::shared_ptr<ISceneNode> kid
) {
    ISceneNode* kid_parent = kid->getParent();
    if (kid_parent) {
        node_id_t kid_id = kid->getNodeID();
        kid_parent->removeChild(kid_id);
    }
}

bool TransformNode::addChild(
    std::shared_ptr<ISceneNode> kid
) {
    if (kid->getParent() == this) {
        return true;
    }
    
    detachParent(kid);
    
    children_.push_back(kid);
    kid->setParent(this);
    
//    Vec3 dir = kid_pos - properties_.getToWorldMatrix().getPosition();
    
//    float new_radius = dir.length() + kid->getProperties()->getRadius();
    
//    if (new_radius > properties_.radius_) {
//        properties_.radius_ = new_radius;
    //}
    
    return true;
}


bool TransformNode::removeChild(
    node_id_t id
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
    T3_TRACE("TransformNode::preRender() - %s\n", getNodeName());
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

std::shared_ptr<TransformNode> TransformNode::createNode(
    const char* const name
) {
    std::shared_ptr<TransformNode> new_node = create(name);
    addChild(new_node);
    return new_node;
}

std::shared_ptr<TransformNode> TransformNode::create(
    const char* const name
) {
    const char* node_name;
    char tmp_name[12];
    if (name == nullptr) {
        //  名前を作る
        node_name = tmp_name;
    }
    else {
        node_name = name;
    }

    std::shared_ptr<TransformNode> new_node;
    new_node.reset(new TransformNode(getNewNodeID(), node_name));
    
    return new_node;
}

}   // namespace theater
}   // namespace t3


