#ifndef TRI_FRAMERATE_HPP_INCLUDED
#define TRI_FRAMERATE_HPP_INCLUDED

namespace t3 {

///
/// フレームレートN時の1フレームあたりの秒数取得
template <int FRAMERATE>
constexpr float frameSec() {
    return 1.0f / FRAMERATE;
}


///
/// フレームを秒に変換
inline float frameToSec(
    int frame   ///< フレーム数
) {
    return static_cast<float>(frame) / 60.0f;
}

///
/// 秒をフレームに変換
inline int secToFrame(
    float sec   ///< 秒
) {
    return static_cast<int>(sec * 60.0f);
}

///
/// デルタタイムあたりのレート
inline float deltaRate(
    float delta_time    ///< 現在のデルタタイム
) {
    return delta_time / frameSec<60>();
}
    
    

}   // namespace t3

#endif // TRI_FRAMERATE_HPP_INCLUDED