#ifndef TRI_SINGLETON_HPP_INCLUDED
#define TRI_SINGLETON_HPP_INCLUDED



#include "../dbg/tri_assert.hpp"
#include "../kernel/tri_kernel.hpp"
#include "util/tri_uncopyable.hpp"



namespace t3{

template <typename T>
class Singleton
    : Uncopyable
{
protected:
    Singleton(){
        T3_ASSERT_MSG(created_ == false, "instance is created.");
        created_ = true;
    }
    ~Singleton(){
        created_ = false;
    }
    
public:
    static void createInstance(){
        instance_ = T3_SYS_NEW T;
    }
    
    // *********************************************
    //  インスタンス破棄
    static void destroyInstance(){
        T3_DELETE instance_;
    }
    
    // *********************************************
    //  インスタンスが生成済か確認
    static bool isCreatedInstance(){
        return instance_ != nullptr;
    }
    
    // *********************************************
    //  インスタンス取得
    static T& instance(){
        T3_ASSERT(created_);
        return *instance_;
    }


private:
    static T* instance_;
    static bool created_;
};

template <typename T> T* Singleton<T>::instance_ = nullptr;
template <typename T> bool Singleton<T>::created_ = false;


}   // namespace t3

#endif // TRI_SINGLETON_HPP_INCLUDED
