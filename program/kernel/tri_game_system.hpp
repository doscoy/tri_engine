#ifndef TRI_GAME_SYSTEM_HPP_INCLUDED
#define TRI_GAME_SYSTEM_HPP_INCLUDED

#include "../tri_develop_base.hpp"

#include "../io/tri_pad.hpp"
#include "../io/tri_pointing.hpp"
#include "../util/random/tri_random.hpp"
#include "../util/tri_singleton.hpp"

#define MAX_PAD 4

//==============================================================================
namespace t3 {

class GameSystem 
    : public Singleton<GameSystem>
{
    friend class Singleton;
    
public:
    typedef RandomNumberGenerator<RandomWell> random_t;
    

private:
    GameSystem();
    ~GameSystem();

public:
// ---------------------------------------------
//  ビューポート管理
    // *********************************************
    //  ビューポートを取得
    const ivec2_t& getScreenSize() const {
        return screen_size_;
    }
    
    // *********************************************
    //  ビューポートを取得
    void setScreenSize( const ivec2_t& vp ) {
        screen_size_ = vp;
    }
    
// ---------------------------------------------
//  乱数管理    
    // *********************************************
    //  乱数ジェネレータを取得
    random_t& getRandomNumberGenerator(){
        return random_number_generator_;
    }
    

    void update( tick_t tick );
    
    bool isSuspend() {
        return suspend_;
    }

    void setSuspend( const bool suspend ){
        suspend_ = suspend;
    }


    const Pad& getPad( const int pad_no = 0 ) const {
        return pad_[pad_no];
    }
    
    const Pad& getDebugPad() const {
        return debug_pad_;
    }

private:
    //  乱数
    random_t random_number_generator_;

    //  ビューポート
    ivec2_t screen_size_;
    
    //  パッド入力
    Pad pad_[MAX_PAD];
    Pad debug_pad_;
    
    bool suspend_;
};


  
}   // namespace t3


#endif // TRI_GAME_SYSTEM_HPP_INCLUDED
