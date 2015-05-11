//
//  ViewController.m
//  tri_sandbox_ios
//
//  Created by KANI Tetsuro on 2014/02/25.
//  Copyright (c) 2014年 KANI Tetsuro. All rights reserved.
//

#import "cross_view_controller.hpp"
#import "cross_types.hpp"
#import <CoreMotion/CoreMotion.h>


float screen_scale_ = 1.0f;
float screen_x_ = 0;
float screen_y_ = 0;
extern cross::PointingData point_data_[4];


@interface CrossViewController () {

}
@property (strong, nonatomic) EAGLContext *context;

@end

@implementation CrossViewController


- (void)viewDidLoad
{

    [super viewDidLoad];
    
    GLKView *view = (GLKView *)self.view;

    self.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    view.context = self.context;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    [EAGLContext setCurrentContext:self.context];
    
    //  FPS設定
    [self setFPS:60];
    
    
}


- (void) setFPS:(int)fps {
    self.preferredFramesPerSecond = fps;
}


- (void)dealloc {
//    t3::terminateApplication();
    
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
    float touch_x = location.x * screen_scale_;
    float touch_y = location.y * screen_scale_;
    float pos_x = touch_x - (screen_x_ / 2);
    float pos_y = -touch_y + (screen_y_ / 2);
    point_data_[0].x_ = pos_x;
    point_data_[0].y_ = pos_y;
}

// 画面に触れている指が一本以上移動したときに実行されるメソッド
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    point_data_[0].hit_ = true;
    UITouch* touch = [touches anyObject];
    CGPoint location = [touch locationInView:self.view];
    float touch_x = location.x * screen_scale_;
    float touch_y = location.y * screen_scale_;
    float pos_x = touch_x - (screen_x_ / 2);
    float pos_y = -touch_y + (screen_y_ / 2);
    point_data_[0].x_ = pos_x;
    point_data_[0].y_ = pos_y;

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



- (void)update {

}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect {

}



@end