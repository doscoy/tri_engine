
#ifndef TRI_MUTEX_HPP_INCLUDED
#define TRI_MUTEX_HPP_INCLUDED

#include <mutex>



namespace t3 {
    

class Mutex {

public:
    Mutex();
    ~Mutex();

    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;

public:
    bool lock();
    void unlock();

};



using ScopedLock = std::lock_guard<t3::Mutex>;


}   // namespace t3

#endif // TRI_MUTEX_HPP_INCLUDED

