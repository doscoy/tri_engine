#include "cross/cross_dbg.hpp"

CROSS_NS_BEGIN
void breakpoint() {
#ifndef _WIN64
    //  x64�ł̓C�����C���A�Z���u���g���܂���
    __asm int 3;
#endif
}
CROSS_NS_END
