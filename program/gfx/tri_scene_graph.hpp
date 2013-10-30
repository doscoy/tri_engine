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



typedef std::map<actor_id_t, std::shared_ptr<ISceneNode>> SceneActorMap;



class CameraNode;
class SkyNode;

class SceneGraph
{
protected:
    std::shared_ptr<SceneNode> root_;
    std::shared_ptr<CameraNode> camera_node_;
    
    MatrixStack matrix_stack_;
    AlphaSceneNodes alpha_scene_nodes_;
    SceneActorMap actor_map_;
    
    void renderAlphaPass();


public:

    SceneGraph();
    virtual ~SceneGraph();
    
    void onRender();
    
    void onRestore();
    
    void onUpdate(tick_t tick);
    
    std::shared_ptr<ISceneNode> findActor( actor_id_t id );
    
    bool addChild(
        actor_id_t id,
        std::shared_ptr<ISceneNode> kid
    ) {
        actor_map_[id] = kid;
        return root_->addChild(kid);
    }

    bool removeChild(
        actor_id_t id
    ) {
        actor_map_.erase(id);
        return root_->removeChild(id);
    }
    
    void setCamera(
        std::shared_ptr<CameraNode> camera
    ) {
        camera_node_ = camera;
    }
    
    const std::shared_ptr<CameraNode> getCamera() const {
        return camera_node_;
    }
    
    void pushAndSetMatrix(
        const mtx4_t& to_world
    );
    
    void popMatrix();
    
    const mtx4_t* getTopMatrix();
    
    void addAlphaSceneNode(
        AlphaSceneNode* asn
    ) {
        alpha_scene_nodes_.push_back(asn);
    }
    
    
};


}   // namespace gfx
}   // namespace t3


#endif
