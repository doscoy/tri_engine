//
//  YsView.m
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/02/11.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//

#import "YsView.h"




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



@implementation YsView

-(void) drawRect: (NSRect) bounds
{
	printf("%s\n",__FUNCTION__);
}

-(void) prepareOpenGL
{
	printf("%s\n",__FUNCTION__);
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

