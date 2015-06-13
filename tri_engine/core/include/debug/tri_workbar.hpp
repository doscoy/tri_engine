/**
    @file tri_workbar.hpp
    ワークバー.
*/
#ifndef TRI_WORKBAR_HPP_INCLUDED
#define TRI_WORKBAR_HPP_INCLUDED

//  include
#include"core_config.hpp"
#include "../utility/tri_uncopyable.hpp"
#include "../math/tri_vec2.hpp"
#include "../graphics/tri_color.hpp"
#include <array>


TRI_CORE_NS_BEGIN


constexpr int MAX_WORKBAR_ITEM = 6;     ///< ワークバー数

///
/// ワークバー
class Workbar
    : private Uncopyable
{
public:
    ///
    /// コンストラクタ
    Workbar();
    
    ///
    /// デストラクタ
    ~Workbar();


public:
    ///
    /// カラーを設定
    void setColor(int index, const Color& color);
    
    ///
    /// パラメータ設定
    void setParam(int index, float param);
    
    ///
    /// 座標を設定
    void position(const Vec2& pos) {
        position_ = pos;
    }
    
    ///
    /// 100%時の数値を設定
    void setLimitParam(float limit) {
        limit_param_ = limit;
    }
    
    ///
    /// 100%時のバーの長さを設定
    void setLimitWidthPixel(int width) {
        limit_width_pixel_ = width;
    }
    
    ///
    ///
    void setTickness(int thickness) {
        thickness_ = thickness;
    }
    
    ///
    /// 描画
    void draw();
    
    
private:
    ///
    /// パラメータ構造体
    struct Param {
        float value_;   ///< 値
        Color color_;   ///< 色
    };
    
    ///
    /// バーのパラメータ集
    Array<Param, MAX_WORKBAR_ITEM> bar_params_;
    
    ///
    /// 数値の限界値
    float limit_param_;
    
    ///
    /// 数値の限界値におけるピクセル数
    int limit_width_pixel_;
    
    ///
    /// リミット値が停止し続けるフレーム数
    int keep_frame_;
    
    ///
    /// 現在のリミット値
    int limit_bar_pos_x_;
    
    ///
    ///
    int thickness_;
    
    ///
    /// 座標
    Vec2 position_;
};


TRI_CORE_NS_END





#endif // TRI_WORKBAR_HPP_INCLUDED
