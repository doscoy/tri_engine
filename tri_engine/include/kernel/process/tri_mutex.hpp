
#ifndef TRI_MUTEX_HPP_INCLUDED
#define TRI_MUTEX_HPP_INCLUDED

#include <pthread.h>
#include <mutex>



namespace t3 {
    

class Mutex {

    using NativeHandle = pthread_mutex_t;
public:
    Mutex();
    ~Mutex();

    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;

public:
    void lock();
    void unlock();

private:
    NativeHandle handle_;
};



using ScopedLock = std::lock_guard<t3::Mutex>;


}   // namespace t3

#endif // TRI_MUTEX_HPP_INCLUDED

