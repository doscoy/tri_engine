////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "jet/scene/jet_scene.hpp"

TRI_JET_NS_BEGIN


Scene::Scene(const char* const name) 
    : core::SceneBase(name)
    , shadow_render_layer_()
    , shadow_render_target_(256,256,Surface::Type::DEPTH_ONLY)
    , scene_layer_()
    , scene_graph_()
{}



Scene::~Scene() {
}

void Scene::initializeScene() {
    T3_RENDER_ASSERT();

    //  レイヤー準備
    shadow_render_layer_.name("shadow_render_layer_");
    shadow_render_layer_.setRenderCallback<Scene>(this, &Scene::shadowRender);
    shadow_render_layer_.renderTarget(&shadow_render_target_);

    //  レイヤー準備
    scene_layer_.name("scene_layer_");
    scene_layer_.setRenderCallback<Scene>(this, &Scene::sceneRender);

    //  シャドウ設定
    shadow_render_layer_.renderTarget(&shadow_render_target_);
    scene_graph_.shadowTexture(shadow_render_target_.depthTexture());
    scene_graph_.shadowProjector()->screenSize(shadow_render_target_.size());



    initialize();
}

void Scene::terminateScene() {
    terminate();
}

void Scene::updateScene(DeltaTime dt) {
    update();
}


TransformNodePtr Scene::createModel(
    const FilePath& path
) {
    ModelPtr model = Model::create(path);
    TransformNodePtr node = scene_graph_.createNode();
    node->entity(model);
    return node;
}

TransformNodePtr Scene::createChildModel(
    const FilePath& path,
    TransformNodePtr& parent
) {
    ModelPtr model = Model::create(path);
    TransformNodePtr node = parent->createNode();
    node->entity(model);
    return node;
}





TRI_JET_NS_END



