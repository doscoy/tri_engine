
#ifndef TRI_METHOD_CALLBACK_HPP_INCLUDED
#define TRI_METHOD_CALLBACK_HPP_INCLUDED

#include "../dbg/tri_assert.hpp"

namespace t3 {


class MethodCallbackBase
{
protected:
    MethodCallbackBase()
        : instance_( nullptr )
        , func_( nullptr )
    {
    }
    
    
protected:
    void* instance_;
    void (MethodCallbackBase::*func_)();
};

template <typename T, typename ReturnType = void>
class MethodCallback
    : public MethodCallbackBase
{
    typedef ReturnType (T::*callback_t)();
    
public:
    MethodCallback(){}
    MethodCallback(
        T* instance,
        callback_t func
    ){
        MethodCallbackBase::instance_ = instance;
        (callback_t&)(MethodCallbackBase::func_) = func;
    }

    bool canInvoke() const {
        if (instance_ == nullptr) {
            return false;
        }
        else if (func_ == nullptr) {
            return false;
        }
        
        return true;
    }
    
    ReturnType invoke() {
        T3_ASSERT(canInvoke());
		T* t = (T*)MethodCallbackBase::instance_;
		callback_t& f = (callback_t&)func_;
        return (t->*(f))();
    }
};


template <typename T, typename Arg1, typename ReturnType = void>
class MethodCallback1
    : public MethodCallbackBase
{
    typedef ReturnType (T::*callback_t)(Arg1);
    
public:
    MethodCallback1(){}
    MethodCallback1(
        T* inst,
        callback_t func
    ){
        MethodCallbackBase::instance_ = inst;
        (callback_t&)(MethodCallbackBase::func_) = func;
    }
    
    ReturnType invoke( Arg1& arg1 ) {
		T* t = (T*)MethodCallbackBase::instance_;
		callback_t& f = (callback_t&)func_;
		return (t->*(f))(arg1);
    }
};

    
template <typename T, typename Arg1, typename Arg2, typename ReturnType = void>
class MethodCallback2
    : public MethodCallbackBase
{
    typedef ReturnType (T::*callback_t)(Arg1, Arg2);
    
    public:
    MethodCallback2(){}
    MethodCallback2(
        T* inst,
        callback_t func
    ){
        MethodCallbackBase::instance_ = inst;
        (callback_t&)(MethodCallbackBase::func_) = func;
    }
    
    ReturnType invoke( Arg1& arg1, Arg2& arg2 ) {
		T* t = (T*)MethodCallbackBase::instance_;
		callback_t& f = (callback_t&)func_;
		return (t->*(f))(arg1, arg2);
	}
};
    
    
template <typename T, typename Arg1, typename Arg2, typename Arg3, typename ReturnType = void>
class MethodCallback3
    : public MethodCallbackBase
{
    typedef ReturnType (T::*callback_t)(Arg1, Arg2);
    
public:
    MethodCallback3(){}
    MethodCallback3(
        T* inst,
        callback_t func
    ){
        MethodCallbackBase::instance_ = inst;
        (callback_t&)(MethodCallbackBase::func_) = func;
    }
    
    ReturnType invoke( Arg1& arg1, Arg2& arg2, Arg3 arg3 ) {
		T* t = (T*)MethodCallbackBase::instance_;
		callback_t& f = (callback_t&)func_;
		return (t->*(f))(arg1, arg2, arg3);
	}
};
    




}   // namespace t3

#endif  // TRI_METHOD_CALLBACK_HPP_INCLUDED
