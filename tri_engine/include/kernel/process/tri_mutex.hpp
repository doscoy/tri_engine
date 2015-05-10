
#ifndef TRI_MUTEX_HPP_INCLUDED
#define TRI_MUTEX_HPP_INCLUDED

//  include
#include <mutex>

namespace t3 {
    
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
using ScopedLock = std::lock_guard<t3::Mutex>;


}   // namespace t3

#endif // TRI_MUTEX_HPP_INCLUDED

