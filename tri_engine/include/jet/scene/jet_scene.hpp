////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
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

///
/// 3Dシーン
class Scene3D
    : public core::SceneBase 
{
public:
    Scene3D(const char* const name);
    ~Scene3D();

public:
    /// このクラスを継承したクラスはこのメソッドを直接オーバーロードできません。
    /// 初期化処理はinitializeをオーバーロードして実装して下さい。
    void initializeScene() final;

    /// このクラスを継承したクラスはこのメソッドを直接オーバーロードできません。
    /// 終了処理はterminateをオーバーロードして実装して下さい。
    void terminateScene() final;

    /// このクラスを継承したクラスはこのメソッドを直接オーバーロードできません。
    /// 更新処理はupdateをオーバーロードして実装して下さい。
    void updateScene(const FrameInfo& frame_info) final;
    
protected:
    TransformNodePtr createModel(const FilePath& path);
    TransformNodePtr createModel(const char* const model_name) {
        return createModel(FilePath(model_name));
    }

    TransformNodePtr createChildModel(
        const FilePath& path,
        TransformNodePtr& parent
    );
    TransformNodePtr createChildModel(
        const char* const model_name,
        TransformNodePtr& parent
    ) {
        return createChildModel(FilePath(model_name), parent);
    }

    SceneGraph& sceneGraph() {
        return scene_graph_;
    }

    Surface& shadowSurface() {
        return shadow_render_target_;
    }

private:
    virtual void initialize() {}
    virtual void terminate() {}
    virtual void update(const FrameInfo& frame_info) {}

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
    DepthSurface shadow_render_target_;

    //  3Dシーン通常描画用レイヤー
    DrawLayer scene_layer_;

    //  シーングラフ
    SceneGraph scene_graph_;
};






///
/// 2Dゲーム用シーンプリセット
class Scene2D
    : public core::SceneBase
{
public:
    ///
    /// コンストラクタ
    Scene2D(const char* const name);

    ///
    /// デストラクタ
    ~Scene2D();
    
public:
    ///
    /// シーン初期化
    /// このクラスを継承したクラスはこのメソッドを直接オーバーロードできません。
    /// 初期化処理はinitializeをオーバーロードして実装して下さい。
    void initializeScene() final;

    ///
    /// シーン後片付け
    /// このクラスを継承したクラスはこのメソッドを直接オーバーロードできません。
    /// 終了処理はterminateをオーバーロードして実装して下さい。
    void terminateScene() final;

    ///
    /// シーン更新
    /// このクラスを継承したクラスはこのメソッドを直接オーバーロードできません。
    /// 更新処理はupdateをオーバーロードして実装して下さい。
    void updateScene(const FrameInfo& frame_info) final;
    
protected:
    auto& defaultSpriteLayer() {
        return default_sprite_layer_;
    }
    
private:
    virtual void initialize() {}
    virtual void terminate() {}
    virtual void update(const FrameInfo& frame_info) {}

private:
    SpriteLayer default_sprite_layer_;
};



TRI_JET_NS_END


#endif // TRI_CONFIG_HPP_INCLUDED

