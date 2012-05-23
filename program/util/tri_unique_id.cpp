#include "tri_unique_id.hpp"

namespace t3 {

// *********************************************
//  ユニークIDを取得
uid_t uniqueID()
{
    static uid_t n = 1; // 0は無効値
    return ++n;
}

}   // namespace t3
