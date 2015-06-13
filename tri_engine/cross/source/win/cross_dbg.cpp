#include "cross_dbg.hpp"

CROSS_NS_BEGIN
void breakpoint() {

    __asm int 3;
}
CROSS_NS_END
