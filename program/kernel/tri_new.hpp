
#ifndef TRI_NEW_HPP_INCLUDED
#define TRI_NEW_HPP_INCLUDED

#include <cstddef>
#include <new>

namespace t3 {
class Heap;
}   // namespace t3


void* operator new(
    ::std::size_t size,
    std::nothrow_t,
    const char* const filename,
    int line
);


#define T3_NEW      ::new(::std::nothrow, __FILE__, __LINE__)
#define T3_DELETE   ::delete

#endif // TRI_NEW_HPP_INCLUDED