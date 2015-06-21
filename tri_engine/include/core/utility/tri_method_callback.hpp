/**
    @file tri_method_callback.hpp
    メソッドコールバック型.
*/

#ifndef TRI_METHOD_CALLBACK_HPP_INCLUDED
#define TRI_METHOD_CALLBACK_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "../debug/tri_assert.hpp"
#include <functional>


TRI_CORE_NS_BEGIN


class MethodCallbackBaseX {
public:
    MethodCallbackBaseX(const void* target)
        : target_(target)
        , arg1_(nullptr)
    {}

    virtual ~MethodCallbackBaseX() = default;
    virtual void invoke() = 0;

    void arg1(void* arg) {
        arg1_ = arg;
    }
    void* arg1() {
        return arg1_;
    }
    const void* target() const {
        return target_;
    }
private:
    ///
    /// インスタンス
    const void* target_;
    void* arg1_;
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
    MethodCallbackX(const T* ins, callback_t callback)
        : MethodCallbackBaseX(ins)
        , func_(callback)
    {}


    ///
    /// 実行
    void invoke() override{
        const T* cp = reinterpret_cast<const T*>(target());
        T3_NULL_ASSERT(cp);
        T* p = const_cast<T*>(cp);
		func_(*p);
	}



protected:
    ///
    /// メンバ関数ポインタ
    callback_t func_;

};

///
/// メソッドコールバック2
template <class T, class Arg1>
class MethodCallbackX1
    : public MethodCallbackBaseX {
public:
    typedef std::function<void(T&, Arg1)> callback_t;

    ///
    /// コンストラクタ
    MethodCallbackX1(const T* ins, callback_t callback)
        : MethodCallbackBaseX(ins)
        , func_(callback)
    {}


    ///
    /// 実行
    void invoke() override{
        const T* cp = reinterpret_cast<const T*>(target());
        T3_NULL_ASSERT(cp);
        T* p = const_cast<T*>(cp);
        Arg1* arg = reinterpret_cast<Arg1*>(arg1());
		func_(*p, *arg);
	}


protected:
    ///
    /// メンバ関数ポインタ
    callback_t func_;
};

TRI_CORE_NS_END

#endif  // TRI_METHOD_CALLBACK_HPP_INCLUDED
