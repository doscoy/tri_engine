
#ifndef TRI_NEW_HPP_INCLUDED
#define TRI_NEW_HPP_INCLUDED

#include <cstddef>


namespace t3 {
class Heap;
}   // namespace t3

void* operator new( ::std::size_t size );
void operator delete( void* mem );

void* operator new( ::std::size_t size, t3::Heap* heap );
void* operator new( ::std::size_t size, const char* const filename, int line );
void operator delete( void* mem, const char* const filename, int line );

#define T3_NEW      ::new( __FILE__, __LINE__ )
#define T3_DELETE   ::delete

#endif // TRI_NEW_HPP_INCLUDED