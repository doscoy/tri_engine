//
//  MyView.m
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/02/11.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//

#include "../platform_sdk.hpp"

#import "MyView.h"
MyView* view_;
@implementation MyView

- (id)initWithFrame:(NSRect)frame pixelFormat:(NSOpenGLPixelFormat*)format
{
    printf("MYVVVVVVVVEEEEEEEEEEEEEWWWWWWWWW\n");

    NSOpenGLPixelFormatAttribute attr[] = {
        NSOpenGLPFADoubleBuffer, // ダブルバッファを使う
        NSOpenGLPFAAccelerated , // ハードウェアアクセラレーションを使う
        NSOpenGLPFAStencilSize , 8, // ステンシルバッファのビット数を32bitにする
        NSOpenGLPFAColorSize , 32, // 画像用バッファのビット数を32bitにする
        NSOpenGLPFADepthSize , 8, // デプスバッファのビット数を32bitにする
        0 // ターミネータ
    };
    NSOpenGLPixelFormat* pFormat;
    pFormat = [ [ [ NSOpenGLPixelFormat alloc ] initWithAttributes : attr ]
               autorelease ];
    
    self = [ super initWithFrame : frame
                    pixelFormat : pFormat ]; // スーパークラスによる初期化
    if (self) {
        
        [ [ self openGLContext ] makeCurrentContext ]; // カレントコンテキストを変更
        ogl::clearColor( 1.0, 0.0, 1.0, 1.0 ); // 背景色を紫にする
    }
    
    view_ = self;
    return self;
}


- (void)drawRect:(NSRect)dirtyRect
{
    ogl::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}



static int YsMacUnicodeToFsKeyCode(int uni)
{
	if(0<=uni && uni<256)
    {
		return FsNormalKeyCode[uni];
    }
	else if(0xf700<=uni && uni<0xf800)
    {
		return FsSpecialKeyCode[uni-0xf700];
    }
	return 0;
}



- (void) keyDown:(NSEvent *)theEvent
{
	unsigned long flags;
	flags=[theEvent modifierFlags];
	NSString *chrs,*chrsNoMod;
	chrs=[theEvent characters];
    
	chrsNoMod=[theEvent charactersIgnoringModifiers];
	if([chrsNoMod length]>0)
    {
		int unicode,fskey;
		unicode=[chrsNoMod characterAtIndex:0];
		fskey=YsMacUnicodeToFsKeyCode(unicode);
        
        if(fskey!=0)
        {
            fsKeyIsDown[fskey]=1;
        }
    }
}

- (void) keyUp:(NSEvent *)theEvent
{
	NSString *chrs,*chrsNoMod;
	chrs=[theEvent characters];
    
	chrsNoMod=[theEvent charactersIgnoringModifiers];
	if([chrsNoMod length]>0)
    {
        int unicode,fskey;
		unicode=[chrsNoMod characterAtIndex:0];
		fskey=YsMacUnicodeToFsKeyCode(unicode);
        
		if(fskey!=0)
        {
			fsKeyIsDown[fskey]=0;
        }
    }
}



@end
