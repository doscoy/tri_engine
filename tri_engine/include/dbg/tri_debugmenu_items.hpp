
#ifndef TRI_DEBUGMENU_ITEMS_HPP_INCLUDED
#define TRI_DEBUGMENU_ITEMS_HPP_INCLUDED

#include "tri_debugmenu_label.hpp"
#include "tri_debugpad.hpp"
#include "tri_debugmenu_frame.hpp"
#include "math/tri_math_types.hpp"
#include <limits.h>
#include <functional>


namespace t3 {
inline namespace dbg {
    
    
void makeTargetValueString(
    const int target,
    char* buf,
    size_t buf_size
);

void makeTargetValueString(
    const double target,
    char* buf,
    size_t buf_size
);

void makeTargetValueString(
    const float target,
    char* buf,
    size_t buf_size
);

void makeTargetValueString(
    const bool target,
    char* buf,
    size_t buf_size
);



template <class T>
class DebugMenuItem
    : public DebugMenuLabel
{
public:
    DebugMenuItem(
        DebugMenuFrame* const parent,
        const char* const label,
        T& target,
        const T step,
        const T low_limit = std::numeric_limits<T>::min(),
        const T high_limit = std::numeric_limits<T>::max()
    )   : DebugMenuLabel( parent, label )
        , target_( target )
        , step_( step )
        , l_limit_( low_limit )
        , h_limit_( high_limit )
    {
    
    }
    
        
public:
    void update() override
    {
        const Pad& pad = debugPad();
        if ( pad.isTrigger(t3::Pad::BUTTON_B)) {
            if (parent_) {
                parent_->setFocusItem(nullptr);
            }
        }
        else if ( pad.isTrigger(t3::Pad::BUTTON_UP)) {
            target_ -= step_;
        }
        else if ( pad.isTrigger(t3::Pad::BUTTON_DOWN)) {
            target_ += step_;
        }
        t3::util::clampLimitation(target_, l_limit_, h_limit_);
    }
    
    
    void draw(
        const float x,
        const float y,
        const Color& color
    ) const override {
        
        char buf[32];
        
        makeTargetValueString(target_, buf, 32);
        
        printDisplay(
            x,
            y,
            color,
            DEBUG_MENU_FONT_SIZE,
            getLabel().c_str()
        );
        
        printDisplay(
            x + (DEBUG_MENU_FONT_SIZE*13),
            y,
            color,
            DEBUG_MENU_FONT_SIZE,
            "%s",
            buf
        );
    }
    
    
private:
    T& target_;
    T step_;
    T l_limit_;
    T h_limit_;
};


    
    
template<>
class DebugMenuItem<Color>
{
    typedef Color item_t;
    typedef uint8_t  step_type_t;
public:
    DebugMenuItem(
        DebugMenuFrame* const parent,
        const char* const label,
        item_t& target,
        const step_type_t step
    )   : dmf_( parent, label )
        , r_( &dmf_, "r", target.red_, step )
        , g_( &dmf_, "g", target.green_, step )
        , b_( &dmf_, "b", target.blue_, step )
        , a_( &dmf_, "a", target.alpha_, step )
    {
    }
    
private:
    DebugMenuFrame dmf_;
    DebugMenuItem<step_type_t> r_;
    DebugMenuItem<step_type_t> g_;
    DebugMenuItem<step_type_t> b_;
    DebugMenuItem<step_type_t> a_;
};
    

template<>
class DebugMenuItem<Vec2>
{
    typedef Vec2 item_t;
    typedef float  step_type_t;
public:
    DebugMenuItem(
        DebugMenuFrame* const parent,
        const char* const label,
        item_t& target,
        const step_type_t step
    )   : dmf_( parent, label )
        , x_( &dmf_, "x", target.x_, step )
        , y_( &dmf_, "y", target.y_, step )
    {
    }
    
private:
    DebugMenuFrame dmf_;
    DebugMenuItem<step_type_t> x_;
    DebugMenuItem<step_type_t> y_;
};

template<>
class DebugMenuItem<Vec3>
{
    typedef Vec3 item_t;
    typedef float  step_type_t;
public:
    DebugMenuItem(
        DebugMenuFrame* const parent,
        const char* const label,
        item_t& target,
        const step_type_t step
    )   : dmf_( parent, label )
        , x_( &dmf_, "x", target.x_, step )
        , y_( &dmf_, "y", target.y_, step )
        , z_( &dmf_, "z", target.z_, step )
    {
    }
    
private:
    DebugMenuFrame dmf_;
    DebugMenuItem<step_type_t> x_;
    DebugMenuItem<step_type_t> y_;
    DebugMenuItem<step_type_t> z_;
};



class DebugMenuButtonBase
    : public DebugMenuLabel
{
public:
    DebugMenuButtonBase(
        DebugMenuFrame* parent,
        const char* const label
    )   : DebugMenuLabel( parent, label )
    {
    }
    
    virtual void invoke() = 0;
    
    void update() override;
    
};

template <typename T, typename ArgType = int>
class DebugMenuButtonFunctor
    : public DebugMenuButtonBase
{
public:
    DebugMenuButtonFunctor(
        DebugMenuFrame* parent,
        const char* const label,
        ArgType param
    )   : DebugMenuButtonBase( parent, label )
        , param_(param)
    {
    }
    
    void invoke() override {
        functor_(param_);
    }
    
private:
    T functor_;
    ArgType  param_;
};


template <typename T>
class DebugMenuButtonMethod
    : public DebugMenuButtonBase
{
public:
    DebugMenuButtonMethod(
        DebugMenuFrame* parent,
        const char* const label,
        T* owner,
        std::function<void(T&)> f
    )   : DebugMenuButtonBase( parent, label )
        , func_(f)
        , owner_(owner)
    {}
    
    void invoke() override {
        T3_NULL_ASSERT(owner_);
        func_(*owner_);
    }
    
private:
    std::function<void(T&)> func_;
    T* owner_;
};






}   // inline namespace dbg
}   // namespace t3

#endif // TRI_DEBUGMENU_ITEMS_HPP_INCLUDED



