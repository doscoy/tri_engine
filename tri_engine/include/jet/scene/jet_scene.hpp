/**
    @file jet_scene.hpp
    ゲームを作るための諸々のレイヤーがプリインストールされたシーン.
*/

#ifndef JET_SCENE_HPP_INCLUDED
#define JET_SCENE_HPP_INCLUDED

#include "jet/jet_config.hpp"
#include "core/base/tri_scene.hpp"
#include "core/graphics/tri_gfx.hpp"

TRI_JET_NS_BEGIN

class Scene 
    : public core::SceneBase 
{
public:
    Scene(const char* const name);
    ~Scene();

public:
    void initializeScene() final;
    void updateScene(tick_t dt) final;
    
protected:
    ModelPtr createModel(FilePath path);


    SceneGraph& sceneGraph() {
        return scene_graph_;
    }


private:
    virtual void initialize() {}
    virtual void update() {}

private:
    void shadowRender() {
        scene_graph_.renderScene(t3::RenderInfo::SHADOW);
    }

    void sceneRender() {
        scene_graph_.renderScene(t3::RenderInfo::NORMAL);
    }

private:
    //  影テクスチャ用レイヤ
    DrawLayer shadow_render_layer_;

    //  影テクスチャ用サーフェス
    Surface shadow_render_target_;

    //  3Dシーン通常描画用レイヤー
    DrawLayer scene_layer_;

    //  シーングラフ
    SceneGraph scene_graph_;
};


TRI_JET_NS_END


#endif // TRI_CONFIG_HPP_INCLUDED

