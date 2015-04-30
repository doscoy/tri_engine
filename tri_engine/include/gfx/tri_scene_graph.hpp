//
//  tri_scene_graph.hpp
//  dev_t3
//
//  Created by 哲郎 可児 on 12/05/24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef dev_t3_tri_scene_graph_hpp
#define dev_t3_tri_scene_graph_hpp

#include "../math/tri_matrix_stack.hpp"
#include "tri_transform_node.hpp"
#include "tri_scene_node.hpp"
#include "tri_camera.hpp"
#include "util/tri_uncopyable.hpp"



namespace t3 {



typedef std::map<NodeID, SceneNodePtr> SceneNodeMap;


class TestObjectNode;
class CameraNode;
class SkyNode;

class SceneGraph
    : Uncopyable
{
public:

    SceneGraph();
    virtual ~SceneGraph();
    
    
public:
    void setupView();
    void renderScene();
    
    void updateScene(tick_t delta_time);
    
    SceneNodePtr findNode( NodeID id );
    
    
    void camera(
        CameraPtr cam
    ) {
        camera_ = cam;
    }
    
    const CameraPtr camera() const {
        return camera_;
    }
    
    const TransformNodePtr getRootNode() const {
        return root_;
    }
    
    void pushAndSetMatrix(
        const Mtx44& to_world
    );
    
    void popMatrix();
    
    const Mtx44* topMatrix();
    
    TransformNodePtr createNode();
    
private:

    bool addChild(
        NodeID id,
        TransformNodePtr kid
    ) {
        node_map_[id] = kid;
        return root_->addChild(kid);
    }

    bool removeChild(
        NodeID id
    ) {
        node_map_.erase(id);
        return root_->removeChild(id);
    }


protected:
    TransformNodePtr root_;
    CameraPtr camera_;
    
    MatrixStack matrix_stack_;
    SceneNodeMap node_map_;
    
};



}   // namespace t3


#endif
