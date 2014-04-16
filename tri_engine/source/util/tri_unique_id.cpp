#include "tri_unique_id.hpp"

namespace t3 {
inline namespace util {

//  ユニークIDを取得
uid_t uniqueID()
{
    static uid_t n = 1; // 0は無効値
    return ++n;
}

}   // namespace util
}   // namespace t3
