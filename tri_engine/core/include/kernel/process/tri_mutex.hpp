/**
    @file tri_mutex.hpp
    ミューテックス.
*/

#ifndef TRI_MUTEX_HPP_INCLUDED
#define TRI_MUTEX_HPP_INCLUDED

//  include
#include "core_config.hpp"
#include <mutex>

TRI_CORE_NS_BEGIN

    
///
/// ミューテックス
class Mutex {

public:
    ///
    /// コンストラクタ
    Mutex();
    
    ///
    /// デストラクタ
    ~Mutex();

    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;

public:
    ///
    /// ロック
    bool lock();
    
    ///
    /// ロック解除
    void unlock();

};


///
/// スコープ内ロック型
using ScopedLock = std::lock_guard<Mutex>;


TRI_CORE_NS_END

#endif // TRI_MUTEX_HPP_INCLUDED

