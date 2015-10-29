////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file cross.hpp
    Web経由告知スクリーン.
*/

#ifndef CROSS_WEB_NOTIFICATION_SCREEN_HPP_INCLUDED
#define CROSS_WEB_NOTIFICATION_SCREEN_HPP_INCLUDED

#include "cross_config.hpp"
#include <memory>

CROSS_NS_BEGIN

class WebNotificationScreen {

public:
    ///
    /// コンストラクタ.
    WebNotificationScreen();

    ///
    /// デストラクタ
    ~WebNotificationScreen();

public:
    ///
    /// 初期化
    void initialize(
        const char* const url   // リクエストするURL
    );
    
    ///
    /// ページを読込中か判定
    bool isLoading() const;


    ///
    /// スクリーンオープン
    void open();
    
    ///
    /// スクリーンクローズ
    void close();

private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};


CROSS_NS_END


#endif  //  CROSS_WEB_NOTIFICATION_SCREEN_HPP_INCLUDED
