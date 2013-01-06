
#ifndef TRI_DEBUGMENU_ITEMS_HPP_INCLUDED
#define TRI_DEBUGMENU_ITEMS_HPP_INCLUDED

#include "tri_develop_base.hpp"
#include "tri_debugmenu_label.hpp"
#include "../io/tri_pad.hpp"
#include "../kernel/tri_game_system.hpp"
#include "tri_debugmenu_frame.hpp"
#include "../kernel/tri_scene.hpp"

namespace t3 {

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
        const T step
    )   : DebugMenuLabel( parent, label )
        , target_( target )
        , step_( step )
    {
    
    }
    
        
public:
    virtual void update() override 
    {
        const Pad& pad = GameSystem::getInstance().getPad();
        if ( pad.isTrigger( t3::PAD_BUTTON_LEFT ) ){
            if ( parent_ ){
                parent_->setFocusItem( nullptr );
            }      
        }
        else if ( pad.isTrigger( t3::PAD_BUTTON_UP ) ){
            target_ -= step_;
        }
        else if ( pad.isTrigger( t3::PAD_BUTTON_DOWN ) ){
            target_ += step_;
        }
    }
    
    
    virtual void draw(
        const float x,
        const float y
    ) const override {
        char buf[32];
        makeTargetValueString( target_, buf, 32 );
        printDisplay( x, y, getLabel() );
        printDisplay( x + (DEBUG_FONT_POINT*13), y, "%s", buf );
    }
    
    
private:
    T& target_;
    T step_;
};


    
    
template<>
class DebugMenuItem<color_t>
{
    typedef color_t item_t;
    typedef u_char  step_type_t;
public:
    DebugMenuItem(
        DebugMenuFrame* const parent,
        const char* const label,
        item_t& target,
        const step_type_t step
    )   : dmf_( parent, label )
        , r_( &dmf_, "r", target.r, step )
        , g_( &dmf_, "g", target.g, step )
        , b_( &dmf_, "b", target.b, step )
        , a_( &dmf_, "a", target.a, step )
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
class DebugMenuItem<vec2_t>
{
    typedef vec2_t item_t;
    typedef float  step_type_t;
public:
    DebugMenuItem(
        DebugMenuFrame* const parent,
        const char* const label,
        item_t& target,
        const step_type_t step
    )   : dmf_( parent, label )
        , x_( &dmf_, "x", target.x, step )
        , y_( &dmf_, "y", target.y, step )
    {
    }
    
private:
    DebugMenuFrame dmf_;
    DebugMenuItem<step_type_t> x_;
    DebugMenuItem<step_type_t> y_;
};

template<>
class DebugMenuItem<vec3_t>
{
    typedef vec3_t item_t;
    typedef float  step_type_t;
public:
    DebugMenuItem(
        DebugMenuFrame* const parent,
        const char* const label,
        item_t& target,
        const step_type_t step
    )   : dmf_( parent, label )
        , x_( &dmf_, "x", target.x, step )
        , y_( &dmf_, "y", target.y, step )
        , z_( &dmf_, "z", target.z, step )
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
    
    virtual void update() override;
    
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
    
    virtual void invoke() override{
        functor_(param_);
    }
    
private:
    T functor_;
    ArgType  param_;
};

template <class T>
class DebugMenuSceneLouncher
    : public DebugMenuLabel
{
public:
    DebugMenuSceneLouncher(
        DebugMenuFrame* parent,
        const char* const label
    )   : DebugMenuLabel( parent, label )
    {
    }

public:
    virtual void update() override{

        GameSystem& gs = GameSystem::getInstance();
        const Pad& pad = gs.getPad();
        if ( pad.isTrigger( PAD_BUTTON_RIGHT ) ){
            SceneManager& sm = SceneManager::getInstance();
            sm.forceChangeScene( gen_.getInstancePtr() );
        }
        else if ( pad.isTrigger( PAD_BUTTON_LEFT ) ){
            parent_->setFocusItem( nullptr );
        }

    }
    TypedSceneGenerator<T> gen_;
};








}   // namespace t3

#endif // TRI_DEBUGMENU_ITEMS_HPP_INCLUDED



