#include "kernel/process/tri_mutex.hpp"

namespace t3 {

std::mutex mtx;

Mutex::Mutex() {

}


Mutex::~Mutex() {

}


bool Mutex::lock() {
    return mtx.try_lock();
}

void Mutex::unlock() {
    mtx.unlock();
}


}   // namespace t3