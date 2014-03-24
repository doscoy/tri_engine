//
//  ViewController.m
//  tri_sandbox_ios
//
//  Created by KANI Tetsuro on 2014/02/25.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#import "ViewController.hpp"

#include "base/tri_application.hpp"
#include "platform/platform.hpp"
#include "AppDelegate.hpp"
#include "dbg/tri_trace.hpp"


int iosMain(int argc, char** argv) {
    
    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([AppDelegate class]));
    }

}

float screen_scale_ = 1.0f;
extern t3::Application* app_;
extern t3::platform::PointingData point_data_[4];

@interface ViewController () {

}
@property (strong, nonatomic) EAGLContext *context;

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];

    if (!self.context) {
        NSLog(@"Failed to create ES context");
    }
    
    GLKView *view = (GLKView *)self.view;
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    //  FPS設定
    self.preferredFramesPerSecond = 60;
    
    [EAGLContext setCurrentContext:self.context];
    
    
    // 各機種で内部の座標系を統一する
    screen_scale_ = [UIScreen mainScreen].scale;

    CGRect bounds = view.bounds;
    float w = bounds.size.width * screen_scale_;
    float h = bounds.size.height * screen_scale_;
    
    t3::initializeTriEngine(w, h, "sandbox");
    app_->initializeApplication();
}

- (void)dealloc
{    
    app_->terminateApplication();
    if ([EAGLContext currentContext] == self.context) {
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

    if ([self isViewLoaded] && ([[self view] window] == nil)) {
        self.view = nil;
        
        
        if ([EAGLContext currentContext] == self.context) {
            [EAGLContext setCurrentContext:nil];
        }
        self.context = nil;
    }

    // Dispose of any resources that can be recreated.
}

// 画面に指を一本以上タッチしたときに実行されるメソッド
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    point_data_[0].hit_ = true;
    UITouch* touch = [touches anyObject];
    CGPoint location = [touch locationInView:self.view];
    point_data_[0].x_ = location.x * screen_scale_;
    point_data_[0].y_ = location.y * screen_scale_;
}

// 画面に触れている指が一本以上移動したときに実行されるメソッド
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    point_data_[0].hit_ = true;
    UITouch* touch = [touches anyObject];
    CGPoint location = [touch locationInView:self.view];
    point_data_[0].x_ = location.x * screen_scale_;
    point_data_[0].y_ = location.y * screen_scale_;
}

// 指を一本以上画面から離したときに実行されるメソッド
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    point_data_[0].hit_ = false;
}

// システムイベントがタッチイベントをキャンセルしたときに実行されるメソッド
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    point_data_[0].hit_ = false;
}


#pragma mark - GLKView and GLKViewController delegate methods

- (void)update
{

    app_->updateApplication();
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{

    app_->renderApplication();
}

#pragma mark -  OpenGL ES 2 shader compilation



@end
