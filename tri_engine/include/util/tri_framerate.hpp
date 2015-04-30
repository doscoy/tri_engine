#ifndef TRI_FRAMERATE_HPP_INCLUDED
#define TRI_FRAMERATE_HPP_INCLUDED

namespace t3 {

    

// *********************************************
//  framerate N の時の1フレームあたりの秒取得

template <int FRAMERATE>
constexpr float frameSec()
{
    return 1.0f / FRAMERATE;
}


inline float frameToSec(int frame)
{
    return static_cast<float>(frame) / 60.0f;
}


inline int secToFrame(float sec)
{
    return static_cast<int>(sec * 60.0f);
}


inline float deltaRate(float delta_time) {
    return delta_time / frameSec<60>();
}
    
    

}   // namespace t3

#endif // TRI_FRAMERATE_HPP_INCLUDED