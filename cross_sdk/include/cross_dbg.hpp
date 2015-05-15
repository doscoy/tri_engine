
#ifndef CROSS_DBG_HPP_INCLUDED
#define CROSS_DBG_HPP_INCLUDED

#include <cassert>

namespace cross {

void breakpoint();

}   // cross


#define CROSS_BREAKPOINT()      cross::breakpoint()
#define CROSS_PANIC()           do{CROSS_BREAKPOINT(); abort();}while(0)
#define CROSS_ASSERT(exp)       do{if(!(exp)) CROSS_PANIC();}while(0)


#endif  // CROSS_DBG_HPP_INCLUDED
