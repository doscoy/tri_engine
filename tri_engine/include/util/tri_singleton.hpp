/**
    @file tri_singleton.hpp
    シングルトン.
*/
#ifndef TRI_SINGLETON_HPP_INCLUDED
#define TRI_SINGLETON_HPP_INCLUDED


//  include
#include "../dbg/tri_assert.hpp"
#include "../kernel/tri_kernel.hpp"
#include "util/tri_uncopyable.hpp"



namespace t3{

///
/// シングルトン
template <typename T>
class Singleton
    : Uncopyable
{
protected:
    ///
    /// コンストラクタ
    Singleton() {
        T3_ASSERT_MSG(created_ == false, "instance is created.");
        created_ = true;
    }
    
    ///
    /// デストラクタ
    ~Singleton(){
        created_ = false;
    }
    
public:
    
    ///
    /// インスタンス生成
    static void createInstance(){
        instance_ = T3_SYS_NEW T;
    }
    
    ///
    ///  インスタンス破棄
    static void destroyInstance(){
        T3_DELETE instance_;
    }
    
    ///
    ///  インスタンスが生成済か確認
    static bool isCreatedInstance(){
        return instance_ != nullptr;
    }
    
    ///
    ///  インスタンス取得
    static T& instance(){
        T3_ASSERT(created_);
        return *instance_;
    }


private:
    static T* instance_;    ///< インスタンス
    static bool created_;   ///< 生成済フラグ
};

template <typename T> T* Singleton<T>::instance_ = nullptr;
template <typename T> bool Singleton<T>::created_ = false;


}   // namespace t3

#endif // TRI_SINGLETON_HPP_INCLUDED
