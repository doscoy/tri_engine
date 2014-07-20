

#ifndef TRI_GUI_BUTTON_HPP_INCLUDED
#define TRI_GUI_BUTTON_HPP_INCLUDED



#include "base/tri_base.hpp"
#include "kernel/tri_kernel.hpp"
#include "gfx/tri_sprite.hpp"
#include "geometry/tri_rectangle.hpp"



namespace t3 {
inline namespace gui {


class Button {
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
    

private:
    void onPointingTrigger(const Event&);
    void onPointingMoving(const Event&);
    void onPointingRelease(const Event&);


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

