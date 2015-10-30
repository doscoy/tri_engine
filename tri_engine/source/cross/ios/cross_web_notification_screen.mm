////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file cross.mm
    Web経由告知スクリーン.
*/
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "cross/cross_web_notification_screen.hpp"


CROSS_NS_BEGIN


class WebNotificationScreen::Impl {
public:
    UIWebView* view_;
};




///
/// コンストラクタ
WebNotificationScreen::WebNotificationScreen()
    : impl_(new WebNotificationScreen::Impl)
{}


///
/// デストラクタ
WebNotificationScreen::~WebNotificationScreen()
{}




///
/// 初期化
void WebNotificationScreen::initialize(
    const char* const url   // リクエストするURL
) {

    impl_->view_ = [[UIWebView alloc] initWithFrame:CGRectMake(0, 0, 200, 300)];
    impl_->view_.scalesPageToFit = YES;
    NSURL* nsurl = [NSURL URLWithString:@"http://www.aquariuscode.com/cm"];
    NSURLRequest* req = [NSURLRequest requestWithURL:nsurl];
    
    UIWindow* window  = [UIApplication sharedApplication].keyWindow;
    auto view = [window rootViewController].view;
    [view addSubview:impl_->view_];
 //   [[UIApplication sharedApplication] openURL:nsurl];
 
     [impl_->view_ loadRequest:req];

 
}

///
/// ページ読み込み判定
bool WebNotificationScreen::isLoading() const {
    return false;
}


///
/// スクリーンオープン
void WebNotificationScreen::open() {

}


///
///
void WebNotificationScreen::close() {

}


CROSS_NS_END

