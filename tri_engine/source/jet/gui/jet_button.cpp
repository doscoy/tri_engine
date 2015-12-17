////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "jet/gui/jet_button.hpp"
#include "core/base/tri_system_events.hpp"
#include "core/geometry/tri_collision.hpp"


namespace t3 {


//  デフォルトのアクティベート処理
void ButtonDefaultActivator::activate(t3::Button *b) {
    
    if (!b->sprite()) {
        return;
    }

    //  色が明るい状態
    b->sprite()->color(color_sample::white());
}

//  デフォルトの非アクティベート処理
void ButtonDefaultActivator::deactivate(t3::Button* b) {

    if (!b->sprite()) {
        return;
    }

    //  色が暗くなる
    b->sprite()->color(color_sample::gray());
}


///
/// ホバー時のエフェクタ
void ButtonDefaultHoverEffector::hover(t3::Button* b) {
    if (!b->sprite()) {
        return;
    }
    //  ちょっと拡大
    b->sprite()->transform()->scale(1.05f);
}

///
/// ホバー解除時のエフェクタ
void ButtonDefaultHoverEffector::unhover(t3::Button* b) {
    if (!b->sprite()) {
        return;
    }
    //  通常サイズに戻す
    b->sprite()->transform()->scale(1.0f);
}


///
/// コンストラクタ
Button::Button()
    : sprite_(nullptr)
    , hit_area_()
    , first_touch_(false)
    , hover_(false)
    , triggerd_events_()
    , activator_(std::make_shared<ButtonDefaultActivator>())
    , hover_effector_(std::make_shared<ButtonDefaultHoverEffector>())
{
    //
    // 各種画面タッチイベントを受ける
    EventManager::addListener(
        this,
        &self_t::onPointingTrigger,
        event::PointingTriggeredEvent::TYPE
    );

    EventManager::addListener(
        this,
        &self_t::onPointingMoving,
        event::PointingMovingEvent::TYPE
    );
    
    EventManager::addListener(
        this,
        &self_t::onPointingRelease,
        event::PointingReleasedEvent::TYPE
    );

}

///
/// デストラクタ
Button::~Button() {
    //  リスナから離脱
    EventManager::removeListener(this);
}


///
/// スプライトの設定
void Button::setupSprite(
    const FilePath path,
    const Vec2 &uv_leftup,
    const Vec2 &uv_size
) {

}

///
/// スプライトの設定
void Button::setupSprite(
    SpritePtr source
) {
    //  スプライトに合わせてサイズを指定
    sprite_ = source;
    sprite_->priority(Sprite::PRIORITY_UI_DEFAULT);
    updateHitArea();
}

///
/// トリガイベントハンドラ
void Button::onPointingTrigger(
    const EventPtr eve
) {
    if (!sprite_) {
        //  スプライトの設定がまだ
        return;
    }
    
    
    //  スプライトがアクティブじゃない場合スキップ
    if (!sprite_->isVisible()) {
        return;
    }
    
    auto trg_event = static_cast<const event::PointingTriggeredEvent*>(eve.get());
    if (isHitPointRectangle(trg_event->position(), hit_area_)) {
        //  ファーストタッチで触っていた
        first_touch_ = true;
        hover();
    }
}

///
/// リリースイベントハンドラ
void Button::onPointingRelease(
    const EventPtr eve
) {
    //  触った状態で離されたか？
    if (hover_) {
        if (!triggerd_events_.empty()) {
            for (auto event: triggerd_events_) {
                EventManager::queueEvent(event);
            }
        }
    }
    
    //  画面から離れたら状態リセット
    first_touch_ = false;
    unhover();

}

///
/// タッチ点移動イベントハンドラ
void Button::onPointingMoving(
    const EventPtr eve
) {
    //  最初のタッチで触ってない場合は無反応
    if (!first_touch_) {
        return;
    }

    
    auto move_event = static_cast<const event::PointingMovingEvent*>(eve.get());
    if (isHitPointRectangle(move_event->position(), hit_area_)) {
        hover();
    }
    else {
        unhover();
    }



}

///
/// アクティベート時の挙動
void Button::activate() {
    activator_->activate(this);
}

///
/// 非アクティベート時の挙動
void Button::deactivate() {
    activator_->deactivate(this);
}


}   // namespace t3

