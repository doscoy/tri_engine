
#ifndef TRI_NEW_HPP_INCLUDED
#define TRI_NEW_HPP_INCLUDED
#include <cstddef>


#define T3_NEW          new(__FILE__, (int)__LINE__)
#define T3_DELETE       delete
#define T3_DELETE_A     delete[]





extern void* operator new(
    ::std::size_t size,
    const char* const filename,
    int line
);
extern void operator delete(
    void* mem,
    const char* const filename,
    int line
);

extern void* operator new[](
    ::std::size_t size,
    const char* const filename,
    int line
);
extern void operator delete[](
    void* mem,
    const char* const filename,
    int line
);



#endif // TRI_NEW_HPP_INCLUDED