//
//  MyView.h
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/02/11.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "YsView.h"
#include "cocoa_keycode.h"

@interface MyView : NSOpenGLView
//- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat*)format;
@end

extern int FsNormalKeyCode[256];

extern int FsSpecialKeyCode[256];


extern int fsKeyIsDown[FSKEY_NUM_KEYCODE];

#define NKEYBUF 256

