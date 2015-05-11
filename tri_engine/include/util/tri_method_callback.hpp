/**
    @file tri_method_callback.hpp
    メソッドコールバック型.
*/

#ifndef TRI_METHOD_CALLBACK_HPP_INCLUDED
#define TRI_METHOD_CALLBACK_HPP_INCLUDED

//  include
#include "../dbg/tri_assert.hpp"

namespace t3 {

///
/// メソッドコールバック
class MethodCallbackBase {
protected:
    ///
    /// コンストラクタ
    MethodCallbackBase()
        : instance_( nullptr )
        , func_( nullptr )
    {}
    
    
protected:
    ///
    /// インスタンス
    void* instance_;

    ///
    /// メンバ関数ポインタ
    void (MethodCallbackBase::*func_)();
};

///
/// 引数無しメンバ関数
template <typename T, typename ReturnType = void>
class MethodCallback
    : public MethodCallbackBase
{
    typedef ReturnType (T::*callback_t)();
    
public:
    ///
    /// コンストラクタ
    MethodCallback() = default;
    
    ///
    /// コンストラクタ
    MethodCallback(
        T* instance,
        callback_t func
    ){
        MethodCallbackBase::instance_ = instance;
        (callback_t&)(MethodCallbackBase::func_) = func;
    }

    ///
    /// 実行可能か判定
    bool canInvoke() const {
        if (instance_ == nullptr) {
            return false;
        }
        else if (func_ == nullptr) {
            return false;
        }
        
        return true;
    }
    
    ///
    /// メソッド実行
    ReturnType invoke() {
        T3_ASSERT(canInvoke());
		T* t = (T*)MethodCallbackBase::instance_;
		callback_t& f = (callback_t&)func_;
        return (t->*(f))();
    }
};

///
/// 引数１つのコールバック
template <typename T, typename Arg1, typename ReturnType = void>
class MethodCallback1
    : public MethodCallbackBase
{
    typedef ReturnType (T::*callback_t)(Arg1);
    
public:
    
    ///
    /// コンストラクタ
    MethodCallback1() = default;
    
    ///
    /// コンストラクタ
    MethodCallback1(
        T* inst,
        callback_t func
    ){
        MethodCallbackBase::instance_ = inst;
        (callback_t&)(MethodCallbackBase::func_) = func;
    }
    
    ///
    /// メソッド実行
    ReturnType invoke( Arg1& arg1 ) {
		T* t = (T*)MethodCallbackBase::instance_;
		callback_t& f = (callback_t&)func_;
		return (t->*(f))(arg1);
    }
};

    
///
/// 引数2つのコールバック
template <typename T, typename Arg1, typename Arg2, typename ReturnType = void>
class MethodCallback2
    : public MethodCallbackBase
{
    typedef ReturnType (T::*callback_t)(Arg1, Arg2);
    
public:
    
    ///
    /// コンストラクタ
    MethodCallback2() = default;
    
    ///
    /// コンストラクタ
    MethodCallback2(
        T* inst,
        callback_t func
    ){
        MethodCallbackBase::instance_ = inst;
        (callback_t&)(MethodCallbackBase::func_) = func;
    }
    
    ///
    /// メソッド実行
    ReturnType invoke( Arg1& arg1, Arg2& arg2 ) {
		T* t = (T*)MethodCallbackBase::instance_;
		callback_t& f = (callback_t&)func_;
		return (t->*(f))(arg1, arg2);
	}
};
    
    
///
/// 引数3つのコールバック
template <typename T, typename Arg1, typename Arg2, typename Arg3, typename ReturnType = void>
class MethodCallback3
    : public MethodCallbackBase
{
    typedef ReturnType (T::*callback_t)(Arg1, Arg2);
    
public:
    
    ///
    /// コンストラクタ
    MethodCallback3() = default;
    
    ///
    /// コンストラクタ
    MethodCallback3(
        T* inst,
        callback_t func
    ){
        MethodCallbackBase::instance_ = inst;
        (callback_t&)(MethodCallbackBase::func_) = func;
    }
    
    ///
    /// メソッド実行
    ReturnType invoke( Arg1& arg1, Arg2& arg2, Arg3 arg3 ) {
		T* t = (T*)MethodCallbackBase::instance_;
		callback_t& f = (callback_t&)func_;
		return (t->*(f))(arg1, arg2, arg3);
	}
};
    




}   // namespace t3

#endif  // TRI_METHOD_CALLBACK_HPP_INCLUDED
