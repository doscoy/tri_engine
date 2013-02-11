//
//  YsView.h
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/02/11.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include "cocoa_keycode.h"

@interface YsView : NSOpenGLView
{
}
- (void) drawRect: (NSRect) bounds;
//- (id)initWithFrame:(NSRect)frameRect pixelFormat:(NSOpenGLPixelFormat*)format;
- (void) prepareOpenGL;
@end


extern int FsNormalKeyCode[256];

extern int FsSpecialKeyCode[256];


extern int fsKeyIsDown[FSKEY_NUM_KEYCODE];

#define NKEYBUF 256
