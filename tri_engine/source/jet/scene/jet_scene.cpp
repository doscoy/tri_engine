////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "jet/scene/jet_scene.hpp"

TRI_JET_NS_BEGIN


Scene3D::Scene3D(const char* const name) 
    : core::SceneBase(name)
    , shadow_render_layer_()
    , shadow_render_target_(256,256,Surface::Type::DEPTH_ONLY)
    , scene_layer_()
    , scene_graph_()
{}



Scene3D::~Scene3D() {
}

void Scene3D::initializeScene() {
    T3_RENDER_ASSERT();

    //  レイヤー準備
    shadow_render_layer_.name("shadow_render_layer_");
    shadow_render_layer_.setRenderCallback<Scene3D>(this, &Scene3D::shadowRender);
    shadow_render_layer_.setupRenderTargetToUserCustom(&shadow_render_target_);

    //  レイヤー準備
    scene_layer_.name("scene_layer_");
    scene_layer_.setRenderCallback<Scene3D>(this, &Scene3D::sceneRender);

    //  シャドウ設定
    shadow_render_layer_.setupRenderTargetToUserCustom(&shadow_render_target_);
    scene_graph_.shadowTexture(shadow_render_target_.depthTexture());
    scene_graph_.shadowProjector()->screenSize(shadow_render_target_.size());



    initialize();
}

void Scene3D::terminateScene() {
    terminate();
}

void Scene3D::updateScene(const DeltaTime dt) {
    update(dt);
}


TransformNodePtr Scene3D::createModel(
    const FilePath& path
) {
    ModelPtr model = Model::create(path);
    TransformNodePtr node = scene_graph_.createNode();
    node->entity(model);
    return node;
}

TransformNodePtr Scene3D::createChildModel(
    const FilePath& path,
    TransformNodePtr& parent
) {
    ModelPtr model = Model::create(path);
    TransformNodePtr node = parent->createNode();
    node->entity(model);
    return node;
}

////////////





///
/// コンストラクタ
Scene2D::Scene2D(const char* const name)
    : core::SceneBase(name)
    , default_sprite_layer_(T3_DEFAULT_SPRITE_LAYER_NAME)
{}


///
/// デストラクタ
Scene2D::~Scene2D() {

}

///
/// シーンの初期化
void Scene2D::initializeScene() {
    initialize();
}

///
/// シーンの後片付け
void Scene2D::terminateScene() {
    terminate();
}

///
/// シーンの更新
void Scene2D::updateScene(const DeltaTime dt) {
    update(dt);
}




TRI_JET_NS_END



