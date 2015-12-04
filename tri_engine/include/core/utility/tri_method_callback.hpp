////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
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

///
/// クラス・メソッドを呼び出すためのホルダー
class MethodCallbackBase {
public:
    ///
    /// コンストラクタ
    MethodCallbackBase()
        : target_(nullptr)
        , arg1_(nullptr)
    {}

    ///
    /// コンストラクタ
    MethodCallbackBase(const void* target)
        : target_(target)
        , arg1_(nullptr)
    {}

    ///
    /// デストラクタ
    virtual ~MethodCallbackBase() = default;

    ///
    /// メソッド呼び出し処理
    virtual void invoke() = 0;

    ///
    /// 引数1を設定
    void arg1(void* arg) {
        arg1_ = arg;
    }
    
    ///
    /// 引数1を取得
    void* arg1() {
        return arg1_;
    }
    
    ///
    /// メソッドに紐付いているクラスインスタンス
    const void* target() const {
        return target_;
    }
private:
    ///
    /// インスタンス
    const void* target_;
    
    /// 引数
    void* arg1_;
};


///
/// メソッドコールバック
template <class T>
class MethodCallback 
    : public MethodCallbackBase {
public:
    typedef std::function<void(T&)> callback_t;

    ///
    /// コンストラクタ
    MethodCallback(const T* ins, callback_t callback)
        : MethodCallbackBase(ins)
        , func_(callback)
    {}


    ///
    /// 実行
    void invoke() override{
        //  何かわからないインスタンスのポインタを強制的に指定の型とみなす
        const T* cp = reinterpret_cast<const T*>(target());
        T3_NULL_ASSERT(cp);
        T* p = const_cast<T*>(cp);
        //  実行！
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
class MethodCallback1
    : public MethodCallbackBase {
public:
    typedef std::function<void(T&, Arg1)> callback_t;

    ///
    /// コンストラクタ
    MethodCallback1(const T* ins, callback_t callback)
        : MethodCallbackBase(ins)
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
