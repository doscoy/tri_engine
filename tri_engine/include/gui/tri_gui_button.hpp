

#ifndef TRI_GUI_BUTTON_HPP_INCLUDED
#define TRI_GUI_BUTTON_HPP_INCLUDED



#include "base/tri_base.hpp"
#include "kernel/tri_kernel.hpp"
#include "gfx/tri_sprite.hpp"
#include "geometry/tri_rectangle.hpp"



namespace t3 {
inline namespace gui {


class Button
    : Uncopyable {
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
    void triggerdEvent(
        EventPtr eve
    ) {
        triggerd_event_ = eve;
    }
    
    SpritePtr sprite() {
        return sprite_;
    }
    
    const SpritePtr sprite() const {
        return sprite_;
    }
    
    void position(const Vec2& pos) {
        T3_NULL_ASSERT(sprite_);
        sprite_->position(pos);
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

private:
    void onPointingTrigger(const Event&);
    void onPointingMoving(const Event&);
    void onPointingRelease(const Event&);

    void updateHitArea() {
        T3_NULL_ASSERT(sprite_);
        hit_area_.setupFromCenterSize(
            sprite_->position(),
            sprite_->size()
        );
    }
    
    
    void hover(bool f) {
        hover_ = f;
        if (sprite_) {
            if (f) {
                sprite_->scale(1.05f);
            }
            else {
                sprite_->scale(1.0f);
            }
        }
    }


private:
    SpritePtr sprite_;
    Rectangle hit_area_;
    bool first_touch_;
    bool hover_;
    EventPtr triggerd_event_;
};   // class Button






}   // namespace gui
}   // namespace t3






#endif // TRI_GUI_BUTTON_HPP_INCLUDED

