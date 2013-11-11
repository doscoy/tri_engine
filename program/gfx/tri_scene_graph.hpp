//
//  tri_scene_graph.hpp
//  dev_t3
//
//  Created by 哲郎 可児 on 12/05/24.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef dev_t3_tri_scene_graph_hpp
#define dev_t3_tri_scene_graph_hpp

#include <map>
#include <memory.h>

#include "../math/tri_matrix_stack.hpp"
#include "tri_scene_node.hpp"



namespace t3 {
inline namespace gfx {



typedef std::map<node_id_t, std::shared_ptr<ISceneNode>> SceneActorMap;


class TestObjectNode;
class CameraNode;
class SkyNode;

class SceneGraph
{
public:

    SceneGraph();
    virtual ~SceneGraph();
    
    void renderScene();
    
    void restoreScene();
    
    void updateScene(tick_t tick);
    
    std::shared_ptr<ISceneNode> findActor( node_id_t id );
    
    
    void setCamera(
        std::shared_ptr<CameraNode> camera
    ) {
        camera_node_ = camera;
    }
    
    const std::shared_ptr<CameraNode> getCamera() const {
        return camera_node_;
    }
    
    const std::shared_ptr<ISceneNode> getRootNode() const {
        return root_;
    }
    
    void pushAndSetMatrix(
        const Mtx4& to_world
    );
    
    void popMatrix();
    
    const Mtx4* getTopMatrix();
    
    void addAlphaSceneNode(
        AlphaSceneNode* asn
    ) {
        alpha_scene_nodes_.push_back(asn);
    }
    
    std::shared_ptr<CameraNode> createCamera();
    std::shared_ptr<TestObjectNode> createTestObject();

private:
    void renderAlphaPass();

    bool addChild(
        node_id_t id,
        std::shared_ptr<ISceneNode> kid
    ) {
        node_map_[id] = kid;
        return root_->addChild(kid);
    }

    bool removeChild(
        node_id_t id
    ) {
        node_map_.erase(id);
        return root_->removeChild(id);
    }

    node_id_t issueNodeID() const {
        next_actor_id_ += 1;
        return next_actor_id_;
    }


protected:
    std::shared_ptr<SceneNode> root_;
    std::shared_ptr<CameraNode> camera_node_;
    
    MatrixStack matrix_stack_;
    AlphaSceneNodes alpha_scene_nodes_;
    SceneActorMap node_map_;
    
    static node_id_t next_actor_id_;
};


}   // namespace gfx
}   // namespace t3


#endif
