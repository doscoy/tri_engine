////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

#include "core/kernel/process/tri_mutex.hpp"

TRI_CORE_NS_BEGIN


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


TRI_CORE_NS_END