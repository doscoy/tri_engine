
#ifndef tri_sandbox_osx_tri_method_callback_hpp
#define tri_sandbox_osx_tri_method_callback_hpp

namespace t3 {
inline namespace util {

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
    
    ReturnType invoke() {
        return (((T*)MethodCallbackBase::instance_)->*((callback_t)func_))();
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
        return (((T*)MethodCallbackBase::instance_)->*((callback_t)func_))(arg1);
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
        return (((T*)MethodCallbackBase::instance_)->*((callback_t)func_))(arg1, arg2);
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
        return (((T*)MethodCallbackBase::instance_)->*((callback_t)func_))(arg1, arg2, arg3);
    }
};
    








}   // inline namespace
}   // namespace t3

#endif
