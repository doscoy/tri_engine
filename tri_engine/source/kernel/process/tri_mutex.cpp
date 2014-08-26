#include "kernel/process/tri_mutex.hpp"

namespace t3 {



Mutex::Mutex()
    : handle_() {
    pthread_mutex_init(&handle_, nullptr);
}


Mutex::~Mutex() {
    pthread_mutex_destroy(&handle_);
}


void Mutex::lock() {
    pthread_mutex_lock(&handle_);
}

void Mutex::unlock() {
    pthread_mutex_unlock(&handle_);
}


}   // namespace t3