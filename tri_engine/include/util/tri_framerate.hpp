#ifndef TRI_FRAMERATE_HPP_INCLUDED
#define TRI_FRAMERATE_HPP_INCLUDED

namespace t3 {
inline namespace util {
    

// *********************************************
//  framerate N の時の1フレームあたりの秒取得

template <int N>
constexpr float frameSec()
{
    return 1.0f / N;
}


inline float frameToSec(int frame)
{
    return static_cast<float>(frame) / 60.0f;
}


inline int secToFrame(float sec)
{
    return sec * 60;
}

    
    
}   // inline namespace util
}   // namespace t3

#endif // TRI_FRAMERATE_HPP_INCLUDED