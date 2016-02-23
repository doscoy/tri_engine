////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file jet_textbox.hpp
    テキストボックス.
*/

#ifndef JET_TEXTBOX_HPP_INCLUDED
#define JET_TEXTBOX_HPP_INCLUDED

//  include
#include "jet/jet_config.hpp"
#include "core/math/tri_vec2.hpp"
#include "core/graphics/tri_sprite_layer.hpp"
#include "core/base/tri_font_glyph.hpp"
#include "core/geometry/tri_transform.hpp"
#include "core/utility/tri_utf8.hpp"

TRI_JET_NS_BEGIN

///
/// テキストボックス
class TextBox {

public:
    ///
    /// x方向アライン種別
    enum class AlignX {
        LEFT,   ///< 左寄せ
        CENTER, ///< 中央寄せ
        RIGHT   ///< 右寄せ
    };
    
    ///
    /// 縦方向アライン種別
    enum class AlignY {
        TOP,    ///< 上詰め
        CENTER, ///< センター
        BOTTOM  ///< 下詰め
    };

public:
    ///
    /// コンストラクタ
    TextBox(SpriteLayer* layer, const GlyphList* glyph_list);

    ///
    /// デストラクタ
    ~TextBox();
    
public:
    ///
    /// テキスト設定
    TextBox& text(const Utf8& text);
    
    ///
    /// 位置設定
    TextBox& center(const Position2D& pos) {
        transform_->position(pos);
        return *this;
    }

    ///
    /// 位置設定
    TextBox& center(float x, float y) {
        transform_->position(x, y);
        return *this;
    }
    
    ///
    /// 位置取得
    const Position2D& center() const {
        return transform_->position();
    }
    
    ///
    /// サイズ設定
    TextBox& size(float w, float h) {
        size_.x_ = w;
        size_.y_ = h;
        return *this;
    }
    
    ///
    /// サイズ設定
    TextBox& size(const Vec2& size) {
        size_ = size;
        return *this;
    }
    
    ///
    /// サイズ取得
    const Vec2& size() const {
        return size_;
    }
    
    ///
    /// 横方向アライン設定
    TextBox& alignX(AlignX align) {
        align_x_ = align;
        return *this;
    }
    
    ///
    /// 縦方向アライン設定
    TextBox& alignY(AlignY align) {
        align_y_ = align;
        return *this;
    }
    
    ///
    /// フォントサイズ設定
    TextBox& fontSize(int size) {
        font_size_ = size;
        return *this;
    }
    
    ///
    /// フォントサイズ取得
    int fontSize() const {
        return font_size_;
    }
    
    ///
    /// フォントカラー設定
    TextBox& fontColor(const t3::Color& c) {
        font_color_ = c;
        return *this;
    }
    
    ///
    /// 親のトランスフォーム設定
    TextBox& parentTransform(t3::Transform2DPtr t) {
        transform_->parent(t);
        return *this;
    }
    
    ///
    /// オートリサイズ設定
    TextBox& autoResize(bool b) {
        auto_resize_ = b;
        return *this;
    }
    
    ///
    /// 設定反映
    void setup() {
        adjustStringLayout();
        updateColor();
    }

    ///
    /// 透明度設定
    TextBox& opacity(int opacity) {
        font_color_.alpha(opacity);
        return *this;
    }
    
    ///
    /// 透明度取得
    int opacity() const {
        return font_color_.alpha();
    }


    ///
    /// テキスト幅取得
    int textWidth() const;
    
private:

    ///
    /// 文字をレイアウトする
    void adjustStringLayout();

    ///
    /// カラー値を更新
    void updateColor();

    ///
    /// 設定したフォントの大きさに対するフォントのスケールの割合を取得
    float fontScaleRatio() const;
    
private:
    SpriteLayer* layer_;            ///< 描画するスプライトレイヤ
    Transform2DPtr transform_;      ///< 姿勢制御情報
    Vec2 size_;                     ///< サイズ
    const GlyphList* glyph_list_;   ///< 使用するフォントグリフ
    const Glyph* unknown_char_glyph_;       ///< 未使用文字の時に使用するグリフ
    std::vector<SpritePtr> char_sprites_;   ///< 文字列用のスプライト
    std::vector<const Glyph*> char_glyphs_; ///< 文字のグリフ
    AlignX align_x_;        ///< 横アライメント
    AlignY align_y_;        ///< 縦アライメント
    int font_size_;         ///< フォントサイズ
    bool auto_resize_;      ///< オートリサイズフラグ
    t3::Color font_color_;  ///< フォントカラー
};


TRI_JET_NS_END


#endif // JET_TEXTBOX_HPP_INCLUDED
