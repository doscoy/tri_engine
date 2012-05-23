
#ifndef TRI_NEW_HPP_INCLUDED
#define TRI_NEW_HPP_INCLUDED


namespace t3 {
class Heap;
}   // namespace t3

void* operator new( size_t size );
void operator delete( void* mem );

void* operator new( size_t size, t3::Heap* heap );



#endif // TRI_NEW_HPP_INCLUDED