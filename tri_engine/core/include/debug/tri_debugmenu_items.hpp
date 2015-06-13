/**
    @file tri_debugmenu_items.hpp
    デバッグメニューアイテム.
*/

#ifndef TRI_DEBUGMENU_ITEMS_HPP_INCLUDED
#define TRI_DEBUGMENU_ITEMS_HPP_INCLUDED

//  include
#include "core_config.hpp"
#include "tri_debugmenu_label.hpp"
#include "tri_debugpad.hpp"
#include "tri_debugmenu_frame.hpp"
#include "math/tri_math_types.hpp"
#include <limits.h>
#include <functional>


TRI_CORE_NS_BEGIN


    
///
/// 数値を文字列化.
/// int値
void makeTargetValueString(
    const int target,
    char* buf,
    size_t buf_size
);

///
/// 数値を文字列化.
/// double値
void makeTargetValueString(
    const double target,
    char* buf,
    size_t buf_size
);

///
/// 数値を文字列化.
/// float値
void makeTargetValueString(
    const float target,
    char* buf,
    size_t buf_size
);

///
/// 数値を文字列化.
/// bool値
void makeTargetValueString(
    const bool target,
    char* buf,
    size_t buf_size
);


///
/// メニューアイテム
template <class T>
class DebugMenuItem
    : public DebugMenuLabel
{
public:
    ///
    /// コンストラクタ
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
    ///
    /// 更新
    void update() override
    {
        const Pad& pad = debugPad();
        if ( pad.isTrigger(t3::Pad::BUTTON_B)) {
            if (parent_) {
                parent_->setFocusItem(nullptr);
            }
        }
        else if ( pad.isTrigger(t3::Pad::BUTTON_UP)) {
            target_ = target_ - step_;
        }
        else if ( pad.isTrigger(t3::Pad::BUTTON_DOWN)) {
            target_ = target_ + step_;
        }
        clampLimitation(target_, l_limit_, h_limit_);
    }
    
    
    ///
    /// 描画
    void draw(
        const float x,
        const float y,
        const Color& color
    ) const override {
        
        char buf[32];
        
        makeTargetValueString(target_, buf, 32);
        
        T3_PRINT_DISP(
            x,
            y,
            color,
            DEBUG_MENU_FONT_SIZE,
            getLabel().c_str()
        );
        
        T3_PRINT_DISP(
            x + (DEBUG_MENU_FONT_SIZE*13),
            y,
            color,
            DEBUG_MENU_FONT_SIZE,
            "%s",
            buf
        );
    }
    
    
private:
    T& target_; ///< 操作対象
    T step_;    ///< 変化量
    T l_limit_; ///< 下限値
    T h_limit_; ///< 上限値
};


///
/// bool値用の値編集メニュー
template <>
class DebugMenuItem<bool>
    : public DebugMenuLabel
{
public:
    ///
    /// コンストラクタ
    DebugMenuItem(
        DebugMenuFrame* const parent,
        const char* const label,
        bool& target
        ) : DebugMenuLabel(parent, label)
        , target_(target)
    {

    }


public:
    ///
    /// 更新
    void update() override
    {
        const Pad& pad = debugPad();
        if (pad.isTrigger(t3::Pad::BUTTON_B)) {
            if (parent_) {
                parent_->setFocusItem(nullptr);
            }
        }
        else if (pad.isTrigger(t3::Pad::BUTTON_UP)) {
            target_ = false;
        }
        else if (pad.isTrigger(t3::Pad::BUTTON_DOWN)) {
            target_ = true;
        }
    }


    ///
    /// 描画
    void draw(
        const float x,
        const float y,
        const Color& color
        ) const override {

        char buf[32];

        makeTargetValueString(target_, buf, 32);

        T3_PRINT_DISP(
            x,
            y,
            color,
            DEBUG_MENU_FONT_SIZE,
            getLabel().c_str()
            );

        T3_PRINT_DISP(
            x + (DEBUG_MENU_FONT_SIZE * 13),
            y,
            color,
            DEBUG_MENU_FONT_SIZE,
            "%s",
            buf
            );
    }


private:
    bool& target_;  ///< 操作対象
};


///
/// Vec2用の値編集メニュー
template<>
class DebugMenuItem<Vec2>
{
    typedef Vec2 item_t;
    typedef float  step_type_t;
public:
    ///
    /// コンストラクタ
    DebugMenuItem(
        DebugMenuFrame* const parent,   ///< 親メニュー
        const char* const label,        ///< ラベル
        item_t& target,                 ///< 操作対象の変数
        const step_type_t step          ///< 変化量
    )   : dmf_( parent, label )
        , x_( &dmf_, "x", target.x_, step )
        , y_( &dmf_, "y", target.y_, step )
    {
    }
    
private:
    DebugMenuFrame dmf_;                ///< フレーム
    DebugMenuItem<step_type_t> x_;      ///< x値
    DebugMenuItem<step_type_t> y_;      ///< y値
};

///
/// Vec3用の値編集メニュー
template<>
class DebugMenuItem<Vec3>
{
    typedef Vec3 item_t;
    typedef float  step_type_t;
public:
    ///
    /// コンストラクタ
    DebugMenuItem(
        DebugMenuFrame* const parent,   ///< 親メニュー
        const char* const label,        ///< ラベル
        item_t& target,                 ///< 操作対象の変数
        const step_type_t step          ///< ステップ量
    )   : dmf_( parent, label )
        , x_( &dmf_, "x", target.x_, step )
        , y_( &dmf_, "y", target.y_, step )
        , z_( &dmf_, "z", target.z_, step )
    {
    }
    
private:
    DebugMenuFrame dmf_;                ///< フレーム
    DebugMenuItem<step_type_t> x_;      ///< x値
    DebugMenuItem<step_type_t> y_;      ///< y値
    DebugMenuItem<step_type_t> z_;      ///< z値
};



///
/// デバッグメニュー用ボタン基底
class DebugMenuButtonBase
    : public DebugMenuLabel
{
public:
    ///
    /// 
    DebugMenuButtonBase(
        DebugMenuFrame* parent,
        const char* const label
    )   : DebugMenuLabel( parent, label )
    {
    }
    
    ///
    /// 
    virtual void invoke() = 0;
    
    ///
    /// 
    void update() override;
    
};


///
///
template <typename T, typename ArgType = int>
class DebugMenuButtonFunctor
    : public DebugMenuButtonBase
{
public:
    ///
    /// 
    DebugMenuButtonFunctor(
        DebugMenuFrame* parent,
        const char* const label,
        ArgType param
    )   : DebugMenuButtonBase( parent, label )
        , param_(param)
    {
    }
    
    ///
    /// 
    void invoke() override {
        functor_(param_);
    }
    
private:
    T functor_;         ///<
    ArgType  param_;    ///<
};

///
///
template <typename T>
class DebugMenuButtonMethod
    : public DebugMenuButtonBase
{
public:
    ///
    /// 
    DebugMenuButtonMethod(
        DebugMenuFrame* parent,
        const char* const label,
        T* owner,
        std::function<void(T&)> f
    )   : DebugMenuButtonBase( parent, label )
        , func_(f)
        , owner_(owner)
    {}
    
    ///
    /// 
    void invoke() override {
        T3_NULL_ASSERT(owner_);
        func_(*owner_);
    }
    
private:
    std::function<void(T&)> func_;  ///<
    T* owner_;                      ///<
};



TRI_CORE_NS_END


#endif // TRI_DEBUGMENU_ITEMS_HPP_INCLUDED



