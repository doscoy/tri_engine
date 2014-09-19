

#ifndef TRI_GUI_BUTTON_HPP_INCLUDED
#define TRI_GUI_BUTTON_HPP_INCLUDED



#include "base/tri_base.hpp"
#include "kernel/tri_kernel.hpp"
#include "gfx/tri_sprite.hpp"
#include "geometry/tri_rectangle.hpp"



namespace t3 {
inline namespace gui {


class Button;
//  ボタンのアクティブ状態変更処理
class ButtonActivator {
public:
    //  コンストラクタ
    ButtonActivator() {
    }
    
    //  デストラクタ
    virtual ~ButtonActivator() {
    }

public:
    //  アクティベート処理
    virtual void activate(Button* b) = 0;

    //  非アクティベート処理
    virtual void deactivate(Button* b) = 0;
};

//  アクティベータポインタ
using ButtonActivatorPtr = SharedPtr<ButtonActivator>;


//  デフォルトのボタンアクティブ状態変更処理
class ButtonDefaultActivator
    : public ButtonActivator {
public:
    //  コンストラクタ
    ButtonDefaultActivator() {
    }
    
    //  デストラクタ
    ~ButtonDefaultActivator() {
    }
    
public:
    //  デフォルトのアクティベート処理
    void activate(Button* b) override;
    
    //  デフォルトの非アクティベート処理
    void deactivate(Button* b) override;
};



//  ホバー状態のエフェクタ
class ButtonHoverEffector {
public:
    //  コンストラクタ
    ButtonHoverEffector() {
    }
    
    //  デストラクタ
    virtual ~ButtonHoverEffector() {
    }
    
public:
    //  ホバー状態
    virtual void hover(Button* b) = 0;

    //  非ホバー状態
    virtual void unhover(Button* b) = 0;
};

//  ホバーエフェクタのポインタ
using ButtonHoverEffectorPtr = SharedPtr<ButtonHoverEffector>;


//  デフォルトのホバーエフェクタ
class ButtonDefaultHoverEffector
    : public ButtonHoverEffector {

public:
    //  コンストラクタ
    ButtonDefaultHoverEffector() {
    }
    
    //  デストラクタ
    ~ButtonDefaultHoverEffector() {
    }
    
public:
    //  ホバー状態
    void hover(Button* b) override;

    //  非ホバー状態
    void unhover(Button* b) override;
};

class Button
    : Uncopyable {
    //  型定義
    using self_t = Button;
    
public:
    Button();
    ~Button();
    
public:
    void setupSprite(
        const FilePath path,
        const Vec2& uv_leftup,
        const Vec2& uv_size
    );
    void setupSprite(
        SpritePtr source
    );
    void addTriggeredEvent(
        EventPtr eve
    ) {
        triggerd_events_.push_back(eve);
    }
    
    SpritePtr sprite() {
        return sprite_;
    }
    
    const SpritePtr sprite() const {
        return sprite_;
    }
    
    void position(const Vec2& pos) {
        T3_NULL_ASSERT(sprite_);
        sprite_->transform()->position(pos);
        updateHitArea();
    }
    
    void size(float s) {
        T3_NULL_ASSERT(sprite_);
        sprite_->size(s);
        sprite_->adjustPivotByCenter();
        updateHitArea();
    }
    
    void size(const Vec2& s) {
        T3_NULL_ASSERT(sprite_);
        sprite_->size(s);
        sprite_->adjustPivotByCenter();
        updateHitArea();
    }
    
    void hitAreaSize(const float s) {
        T3_NULL_ASSERT(sprite_);
        hit_area_.size(t3::Vec2(s, s));
    }
    
    void hitAreaSize(const Vec2& s) {
        T3_NULL_ASSERT(sprite_);
        hit_area_.size(s);
    }
    
    void activator(ButtonActivatorPtr activator) {
        activator_ = activator;
    }
    
    
    UniqueID buttonID() const {
        return button_id_;
    }
    
    void activate();
    void deactivate();

private:
    void onPointingTrigger(const Event&);
    void onPointingMoving(const Event&);
    void onPointingRelease(const Event&);

    void updateHitArea() {
        T3_NULL_ASSERT(sprite_);
        hit_area_.setupFromCenterSize(
            sprite_->transform()->position(),
            sprite_->size()
        );
    }
    
    
    void hover() {
        hover_ = true;
        hover_effector_->hover(this);
    }
    
    void unhover() {
        hover_ = false;
        hover_effector_->unhover(this);
    }


private:
    SpritePtr sprite_;
    Rectangle hit_area_;
    bool first_touch_;
    bool hover_;
    Vector<EventPtr> triggerd_events_;
    ButtonActivatorPtr activator_;
    ButtonHoverEffectorPtr hover_effector_;
    UniqueID button_id_;

};   // class Button






}   // namespace gui
}   // namespace t3






#endif // TRI_GUI_BUTTON_HPP_INCLUDED

