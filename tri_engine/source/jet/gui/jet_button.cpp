

#include "jet/gui/jet_button.hpp"
#include "core/base/tri_system_events.hpp"
#include "core/geometry/tri_collision.hpp"


namespace t3 {


//  デフォルトのアクティベート処理
void ButtonDefaultActivator::activate(t3::Button *b) {
    
    if (!b->sprite()) {
        return;
    }

    b->sprite()->color(color_sample::white());

}

//  デフォルトの非アクティベート処理
void ButtonDefaultActivator::deactivate(t3::Button* b) {

    if (!b->sprite()) {
        return;
    }

    b->sprite()->color(color_sample::gray());
}


void ButtonDefaultHoverEffector::hover(t3::Button* b) {
    if (!b->sprite()) {
        return;
    }
    b->sprite()->transform()->scale(1.05f);
}

void ButtonDefaultHoverEffector::unhover(t3::Button* b) {
    if (!b->sprite()) {
        return;
    }
    b->sprite()->transform()->scale(1.0f);
}


Button::Button()
    : sprite_(nullptr)
    , hit_area_()
    , first_touch_(false)
    , hover_(false)
    , triggerd_events_()
    , activator_(std::make_shared<ButtonDefaultActivator>())
    , hover_effector_(std::make_shared<ButtonDefaultHoverEffector>())
{
    EventManager::addListener<Button>(
        this,
        &self_t::onPointingTrigger,
        PointingTriggeredEvent::TYPE
    );

    EventManager::addListener<Button>(
        this,
        &self_t::onPointingMoving,
        PointingMovingEvent::TYPE
    );
    
    EventManager::addListener<Button>(
        this,
        &self_t::onPointingRelease,
        PointingReleasedEvent::TYPE
    );

}

Button::~Button() {
    EventManager::removeListener(this);
}


void Button::setupSprite(
    const FilePath path,
    const Vec2 &uv_leftup,
    const Vec2 &uv_size
) {

}

void Button::setupSprite(
    SpritePtr source
) {
    sprite_ = source;
    sprite_->priority(Sprite::PRIORITY_UI_DEFAULT);
    updateHitArea();
}


void Button::onPointingTrigger(
    const EventPtr eve
) {
    if (!sprite_) {
        //  スプライトの設定がまだ
        return;
    }
    
    
    //  スプライトがアクティブじゃない場合スキップ
    if (!sprite_->enabled()) {
        return;
    }
    
    auto trg_event = static_cast<const PointingTriggeredEvent*>(eve.get());
    if (isHitPointRectangle(trg_event->position(), hit_area_)) {
        //  ファーストタッチで触っていた
        first_touch_ = true;
        hover();
    }
}

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

void Button::onPointingMoving(
    const EventPtr eve
) {
    //  最初のタッチで触ってない場合は無反応
    if (!first_touch_) {
        return;
    }

    
    auto move_event = static_cast<const t3::PointingMovingEvent*>(eve.get());
    if (isHitPointRectangle(move_event->position(), hit_area_)) {
        hover();
    }
    else {
        unhover();
    }



}

void Button::activate() {
    activator_->activate(this);
}

void Button::deactivate() {
    activator_->deactivate(this);
}


}   // namespace t3

