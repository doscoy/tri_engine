////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file jet_button.hpp
    ボタン.
    ボタンの挙動は外部からActivator, Effectorにより置き換える設計です。
    押された時、カーソルが乗った（ホバー状態）などの状態による挙動を指定することで
    任意の挙動のボタンにカスタマイズできます。何も指定が無い場合デフォルトの挙動用の
    Activator, Effectorが設定されます。
*/

#ifndef JET_BUTTON_HPP_INCLUDED
#define JET_BUTTON_HPP_INCLUDED


//  include
#include "jet/jet_config.hpp"
#include "core/base/tri_base.hpp"
#include "core/kernel/tri_kernel.hpp"
#include "core/graphics/tri_sprite.hpp"
#include "core/geometry/tri_rectangle.hpp"



TRI_JET_NS_BEGIN


//  前方宣言
class Button;

///
///  ボタンのアクティブ状態変更処理
class ButtonActivator {
public:
    ///
    ///  コンストラクタ
    ButtonActivator() {
    }
    
    ///
    ///  デストラクタ
    virtual ~ButtonActivator() {
    }

public:
    ///
    ///  アクティベート処理
    virtual void activate(Button* b) = 0;

    ///
    ///  非アクティベート処理
    virtual void deactivate(Button* b) = 0;
};

///
///  アクティベータポインタ
using ButtonActivatorPtr = SharedPtr<ButtonActivator>;

///
///  デフォルトのボタンアクティブ状態変更処理
class ButtonDefaultActivator
    : public ButtonActivator {
public:
    ///
    ///  コンストラクタ
    ButtonDefaultActivator() {
    }
    
    ///
    ///  デストラクタ
    ~ButtonDefaultActivator() {
    }
    
public:
    ///
    ///  デフォルトのアクティベート処理
    void activate(Button* b) override;
    

    ///
    ///  デフォルトの非アクティベート処理
    void deactivate(Button* b) override;
};


///
///  ホバー状態のエフェクタ
class ButtonHoverEffector {
public:
    ///
    ///  コンストラクタ
    ButtonHoverEffector() {
    }
    
    ///
    ///  デストラクタ
    virtual ~ButtonHoverEffector() {
    }
    
public:
    ///
    ///  ホバー状態
    virtual void hover(Button* b) = 0;

    ///
    ///  非ホバー状態
    virtual void unhover(Button* b) = 0;
};

///
///  ホバーエフェクタのポインタ
using ButtonHoverEffectorPtr = SharedPtr<ButtonHoverEffector>;

///
///  デフォルトのホバーエフェクタ
class ButtonDefaultHoverEffector
    : public ButtonHoverEffector {

public:
    ///
    ///  コンストラクタ
    ButtonDefaultHoverEffector() {
    }
    
    ///
    ///  デストラクタ
    ~ButtonDefaultHoverEffector() {
    }
    
public:
    ///
    ///  ホバー状態
    void hover(Button* b) override;

    /// 
    /// 非ホバー状態
    void unhover(Button* b) override;
};

///
/// ボタン
class Button
    : Uncopyable {
    //  型定義
    using self_t = Button;
    
public:
    ///
    /// コンストラクタ
    Button();

    ///
    /// デストラクタ
    ~Button();
    
public:
    ///
    /// スプライト読み込み
    void setupSprite(
        const FilePath path,    ///< ファイルパス
        const Vec2& uv_leftup,  ///< 左上座標
        const Vec2& uv_size     ///< サイズ
    );

    ///
    /// スプライト設定
    void setupSprite(
        SpritePtr source    ///< 既存のスプライト
    );

    ///
    /// ボタントリガ時に発動するイベント設定
    void addTriggeredEvent(
        EventPtr eve
    ) {
        triggerd_events_.push_back(eve);
    }
    
    ///
    /// スプライト取得
    SpritePtr sprite() {
        return sprite_;
    }
    
    ///
    /// スプライト取得
    const SpritePtr sprite() const {
        return sprite_;
    }
    
    ///
    /// ボタン位置設定
    void position(const Vec2& pos) {
        T3_NULL_ASSERT(sprite_);
        sprite_->transform()->position(pos);
        updateHitArea();
    }
    
    ///
    /// ボタンサイズ設定
    void size(float s) {
        T3_NULL_ASSERT(sprite_);
        sprite_->size(s);
        sprite_->adjustPivotByCenter();
        updateHitArea();
    }
    
    ///
    /// ボタンサイズ設定
    void size(const Vec2& s) {
        T3_NULL_ASSERT(sprite_);
        sprite_->size(s);
        sprite_->adjustPivotByCenter();
        updateHitArea();
    }
    
    ///
    /// 判定エリア設定
    void hitAreaSize(const float s) {
        T3_NULL_ASSERT(sprite_);
        hit_area_.size(t3::Vec2(s, s));
    }
    
    ///
    /// 判定エリア設定
    void hitAreaSize(const Vec2& s) {
        T3_NULL_ASSERT(sprite_);
        hit_area_.size(s);
    }
    
    ///
    /// アクティベータ設定
    void activator(ButtonActivatorPtr activator) {
        activator_ = activator;
    }
    
    
    ///
    /// ボタンID
    UniqueID buttonID() const {
        return button_id_;
    }
    
    ///
    /// アクティブ化
    void activate();

    ///
    /// 非アクティブ化
    void deactivate();

private:

    ///
    /// トリガイベントレシーバ
    void onPointingTrigger(const EventPtr);

    ///
    /// ポイントムーブイベントレシーバ
    void onPointingMoving(const EventPtr);

    ///
    /// リリースイベントレシーバ
    void onPointingRelease(const EventPtr);

    ///
    /// 判定エリア更新
    void updateHitArea() {
        T3_NULL_ASSERT(sprite_);
        hit_area_.setupFromCenterSize(
            sprite_->transform()->position(),
            sprite_->size()
        );
    }
    
    
    ///
    /// ホバー
    void hover() {
        hover_ = true;
        hover_effector_->hover(this);
    }
    
    ///
    /// ホバー解除
    void unhover() {
        hover_ = false;
        hover_effector_->unhover(this);
    }


private:
    SpritePtr sprite_;          ///< 使用するスプライト
    Rectangle hit_area_;        ///< 判定エリア
    bool first_touch_;          ///< 触ったか判定
    bool hover_;                ///< ホバー中フラグ
    Vector<EventPtr> triggerd_events_;          ///< ボタンが押された時に発動するイベント
    ButtonActivatorPtr activator_;              ///< アクティブ挙動制御
    ButtonHoverEffectorPtr hover_effector_;     ///< ホバー挙動制御
    UniqueID button_id_;        ///< ボタンID

};   // class Button


TRI_JET_NS_END




#endif // JET_BUTTON_HPP_INCLUDED



