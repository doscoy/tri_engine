//
//  tri_scene_node_properties.hpp
//  dev_t3
//
//  Created by 哲郎 可児 on 12/05/23.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef dev_t3_tri_scene_node_properties_hpp
#define dev_t3_tri_scene_node_properties_hpp

#include "../math/tri_math.hpp"
#include "tri_material.hpp"
#include <string>

namespace t3 {
inline namespace gfx {

typedef unsigned int actor_id_t;

enum RenderPass {
    RENDER_PASS_0,          // 開始パス
    RENDER_PASS_STATIC,     // 環境とレベルジオメトリ
    RENDER_PASS_ACTOR,      // 移動可能オブジェクト
    RENDER_PASS_SKY,        // 遠景
    RENDER_PASS_LAST,       // ループカウンタ
};


enum AlphaType {
    ALPHA_MATERIAL,
    ALPHA_OPAQUE,
    NORMAL_MATERIAL,
};

class SceneNodeProperties
{
    friend class SceneNode;
    
public:
    SceneNodeProperties(
        actor_id_t id,
        std::string name,
        RenderPass render_pass,
        AlphaType alpha_type
    );
    
protected:
    actor_id_t actor_id_;
    std::string name_;
    mtx4_t to_world_;
    mtx4_t from_world_;
    float radius_;
    RenderPass render_pass_;
    Material material_;
    AlphaType alpha_type_;
    
    
    void setOpacity(
        const float alpha
    ) {
        alpha_type_ = ALPHA_MATERIAL;
        material_.setOpacity(alpha);
    }
    
public:
    const actor_id_t getActorId() const {
        return actor_id_;
    }
    
    const mtx4_t& getToWorld() const {
        return to_world_;
    }
    
    const mtx4_t& getFromWorld() const {
        return from_world_;
    }
    
    void getTransformMatrix(
        mtx4_t* to_world,
        mtx4_t* from_world
    ) const;
    
    const char* getName() const {
        return name_.c_str();
    }
    
    bool hasAlpha() const {
        return material_.hasAlpha();
    }
    
    virtual float getOpacity() const {
        return material_.getOpacity();
    }
    
    RenderPass getRenderPass() const {
        return render_pass_;
    }
    
    float getRadius() const {
        return radius_;
    }
    
    mtx4_t& getToWorldMatrix() {
        return to_world_;
    }
    
    const mtx4_t& getToWorldMatrix() const {
        return to_world_;
    }
    
    mtx4_t& getFromWorldMatrix() {
        return from_world_;
    }
    
    const mtx4_t& getFromWorldMatrix() const {
        return from_world_;
    }
    
    
    const Material& getMaterial() const {
        return material_;
    }
    
};


}   // namespace gfx
}   // namespace t3

#endif
