////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_singleton.hpp
    シングルトン.
*/
#ifndef TRI_SINGLETON_HPP_INCLUDED
#define TRI_SINGLETON_HPP_INCLUDED


//  include
#include "core/core_config.hpp"
#include "core/debug/tri_assert.hpp"
#include "core/kernel/memory/tri_new.hpp"
#include "core/utility/tri_uncopyable.hpp"



TRI_CORE_NS_BEGIN


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
    static auto& createInstance(){
        instance_ = T3_SYS_NEW T;
        return instance();
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


TRI_CORE_NS_END

#endif // TRI_SINGLETON_HPP_INCLUDED
