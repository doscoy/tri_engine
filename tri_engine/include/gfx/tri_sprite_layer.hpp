/**
    @file tri_sprite_layer.hpp
    スプライト表示用レイヤー.
*/

#ifndef TRI_SPRITE_LAYER_HPP_INCLUDED
#define TRI_SPRITE_LAYER_HPP_INCLUDED

//  include
#include "tri_render_layer.hpp"
#include "tri_sprite.hpp"
#include "tri_sprite_renderer.hpp"
#include <list>
#include <memory.h>

namespace t3 {

///
/// スプライトレイヤー
class SpriteLayer
    : public RenderLayer
{
public:
    ///
    /// スプライトコンテナ
    using SpriteContainer = List<WeakSprite>;

public:
    ///
    /// コンストラクタ
    SpriteLayer();
    
    ///
    /// コンストラクタ
    SpriteLayer(
        const String& name, ///< レイヤー名
        const int priority = PRIORITY_APP_DEFAULT   ///< プライオリティ
    );
    
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
    
private:
    ///
    /// スプライトを登録
    void attachSprite(
        WeakSprite const sprite ///< スプライト
    );
    
    ///
    /// スプライトを全て解除
    void detachAllSprite();

    ///
    /// レイヤーの更新
    void updateLayer(tick_t delta_time) override;
    
    ///
    /// レイヤーの描画
    void drawLayer() override;
    
private:
    ///
    /// スプライトレンダラ
    SpriteRenderer renderer_;
    
    ///
    /// スプライトコンテナ
    SpriteContainer sprites_;
    
};


}   // namespace t3



#endif // TRI_SPRITE_LAYER


