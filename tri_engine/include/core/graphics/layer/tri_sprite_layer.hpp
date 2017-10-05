////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_sprite_layer.hpp
    スプライト表示用レイヤー.
*/

#ifndef TRI_SPRITE_LAYER_HPP_INCLUDED
#define TRI_SPRITE_LAYER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/graphics/layer/tri_layer_base.hpp"
#include "core/graphics/tri_sprite.hpp"
#include "core/graphics/tri_sprite_renderer.hpp"
#include <list>
#include <memory.h>

TRI_CORE_NS_BEGIN


///
/// スプライトレイヤー
class SpriteLayer;
using SpriteLayerPtr = SharedPtr<SpriteLayer>;
class SpriteLayer
    : public LayerBase
{
public:
    ///
    /// スプライトコンテナ
    using SpriteContainer = List<SpriteWeakPtr>;

protected:

    ///
    /// コンストラクタ
    SpriteLayer(
        const String& name,                     ///< レイヤー名
        const LayerBase::Priority priority      ///< プライオリティ
    );

public:
    
    ///
    /// デストラクタ
    virtual ~SpriteLayer();

public:
    
    ///
    /// スプライトを生成
    SpritePtr createSprite(
        TexturePtr tex  ///< テクスチャ
    );
    
    ///
    /// スプライトを生成
    SpritePtr createSprite(
        const String& tex_name  ///< ファイル名
    );

    ///
    /// スプライトコンテナを取得
    SpriteContainer* getManagementSprites() {
        return &sprites_;
    }

    ///
    /// レンダラを取得
    SpriteRenderer& renderer() {
        return renderer_;
    }

    
protected:
    ///
    /// 管理領域から未使用のスプライトを探す
    SpritePtr newSprite();

    ///
    /// レイヤーの更新
    void updateLayer(const FrameInfo& frame_info) override;
    
    ///
    /// レイヤーの描画
    void renderLayer() override;
    

public:
    static SpriteLayerPtr create(
        const String& name = "Sprite",                         ///< レイヤー名
        const LayerBase::Priority priority = Priority::DEFAULT   ///< プライオリティ
    ) {
        SpriteLayerPtr layer(T3_SYS_NEW SpriteLayer(name, priority));
        layer->setupRenderTargetToSystem();
        return layer;
    }

private:
    ///
    /// スプライトレンダラ
    SpriteRenderer renderer_;
    
    ///
    /// スプライトコンテナ
    SpriteContainer sprites_;
    
};


TRI_CORE_NS_END



#endif // TRI_SPRITE_LAYER

