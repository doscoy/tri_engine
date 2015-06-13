
#ifndef CROSS_DBG_HPP_INCLUDED
#define CROSS_DBG_HPP_INCLUDED

#include <cassert>
#include "cross_config.hpp"

CROSS_NS_BEGIN

void breakpoint();



#define CROSS_BREAKPOINT()      cross::breakpoint()
#define CROSS_PANIC()           do{CROSS_BREAKPOINT(); abort();}while(0)
#define CROSS_ASSERT(exp)       do{if(!(exp)) CROSS_PANIC();}while(0)

CROSS_NS_END

#endif  // CROSS_DBG_HPP_INCLUDED
