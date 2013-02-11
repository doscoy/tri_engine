//
//  MyView.m
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/02/11.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//

#import "MyView.h"
MyView* view_;
@implementation MyView

- (id)initWithFrame:(NSRect)frame
{
    printf("MYVVVVVVVVEEEEEEEEEEEEEWWWWWWWWW");
    
    NSOpenGLPixelFormatAttribute attr[] = {
        NSOpenGLPFADoubleBuffer, // ダブルバッファを使う
        NSOpenGLPFAAccelerated , // ハードウェアアクセラレーションを使う
        NSOpenGLPFAStencilSize , 32, // ステンシルバッファのビット数を32bitにする
        NSOpenGLPFAColorSize , 32, // 画像用バッファのビット数を32bitにする
        NSOpenGLPFADepthSize , 32, // デプスバッファのビット数を32bitにする
        0 // ターミネータ
    };
    NSOpenGLPixelFormat* pFormat;
    pFormat = [ [ [ NSOpenGLPixelFormat alloc ] initWithAttributes : attr ]
               autorelease ];
    
    self = [ super initWithFrame : frame
                    pixelFormat : pFormat ]; // スーパークラスによる初期化
    if (self) {
        
        [ [ self openGLContext ] makeCurrentContext ]; // カレントコンテキストを変更
        glClearColor( 1.0, 0.0, 1.0, 1.0 ); // 背景色を紫にする
    }
    view_ = self;
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
//    printf("DDDRRRAAAAWWWW");
//    [[self openGLContext] flushBuffer];
  //  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//    glFinish();

}

@end
