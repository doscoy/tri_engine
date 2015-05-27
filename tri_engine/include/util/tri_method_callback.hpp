/**
    @file tri_method_callback.hpp
    メソッドコールバック型.
*/

#ifndef TRI_METHOD_CALLBACK_HPP_INCLUDED
#define TRI_METHOD_CALLBACK_HPP_INCLUDED

//  include
#include "../dbg/tri_assert.hpp"
#include <functional>


namespace t3 {

///
/// メソッドコールバック
class MethodCallbackBase {
protected:
    ///
    /// コンストラクタ
    MethodCallbackBase()
        : target_( nullptr )
        , func_( nullptr )
    {}
    

    MethodCallbackBase(void* ins)
        : target_(ins)
        , func_(nullptr)
    {}


public:
    void* target() {
        return target_;
    }

    void* func() {

        return func_;
    }
    

    ///
    /// 実行可能か判定
    bool canInvoke() const {
        if (!target_) {
            return false;
        }
        else if (!func_) {
            return false;
        }
        
        return true;
    }
    

protected:
    ///
    /// インスタンス
    void* target_;

    ///
    /// メンバ関数ポインタ
//    void (T::*func_)();
    void* func_;

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
    MethodCallback(
        T* instance,
        callback_t func
    ) : MethodCallbackBase(instance)
    {
        (callback_t&)(MethodCallbackBase::func_) = func;
    }


    ///
    /// メソッド実行
    ReturnType invoke() {
        T3_ASSERT(canInvoke());
		T* t = (T*)target();
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
    MethodCallback1(
        T* inst,
        callback_t func
    ) : MethodCallbackBase(inst)   
    {
        (callback_t&)func_ = func;
    }
    
    ///
    /// メソッド実行
    ReturnType invoke( Arg1& arg1 ) {
		T* t = (T*)target();
//		callback_t f = (callback_t);
		return (t->*((callback_t&)func_))(arg1);
    }

    template <class X, class Y>
    MethodCallback1& operator =(MethodCallback1<X, Y>& rhs) {
        target_ = rhs.target();
        void* p = rhs.func();
        func_ = p;
        return *this;
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
    MethodCallback2(
        T* inst,
        callback_t func
    ) : MethodCallbackBase(inst)   
    {
        (callback_t&)(MethodCallbackBase::func_) = func;
    }
    
    ///
    /// メソッド実行
    ReturnType invoke( Arg1& arg1, Arg2& arg2 ) {
		T* t = (T*)target();
        T* u = nullptr;
        callback_t& f = reinterpret_cast<callback_t&>(*(&func_));
		return (u->*f)(arg1, arg2);
	}


    template <class X, class Y, class Z>
    MethodCallback2& operator =(MethodCallback2<X, Y, Z>& rhs) {
        target_ = rhs.target();
        func_ = rhs.func();
        return *this;
    }

};
    
/*
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
    

*/


class MethodCallbackBaseX {
public:
    MethodCallbackBaseX() = default;
    virtual ~MethodCallbackBaseX() = default;
    virtual void invoke() = 0;
};


///
/// メソッドコールバック
template <class T>
class MethodCallbackX 
    : public MethodCallbackBaseX {
public:
    typedef std::function<void(T&)> callback_t;

    ///
    /// コンストラクタ
    MethodCallbackX(T* ins, callback_t& callback)
        : target_(ins)
        , func_(callback)
    {}


    ///
    /// 実行
    void invoke() override{
		func_(*target_);
	}


protected:
    ///
    /// インスタンス
    T* target_;

    ///
    /// メンバ関数ポインタ
    std::function<void(T&)> func_;

};


}   // namespace t3

#endif  // TRI_METHOD_CALLBACK_HPP_INCLUDED
