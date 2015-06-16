
#include "jet/scene/jet_scene.hpp"

TRI_JET_NS_BEGIN


Scene::Scene(const char* const name) 
    : core::SceneBase(name)
    , shadow_render_layer_()
    , shadow_render_target_()
    , scene_layer_()
    , scene_graph_()
{}



Scene::~Scene() {
}

void Scene::initializeScene() {
    //  レイヤー準備
    shadow_render_layer_.name("shadow_render_layer_");
    shadow_render_layer_.setRenderCallback<Scene>(this, &Scene::shadowRender);

    //  レイヤー準備
    scene_layer_.name("scene_layer_");
    scene_layer_.setRenderCallback<Scene>(this, &Scene::sceneRender);


    initialize();
}

void Scene::updateScene(tick_t dt) {
    update();
}


ModelPtr createModel(
    const FilePath& path
) {
    return Model::create(path.fullpath().c_str());
}


TRI_JET_NS_END



