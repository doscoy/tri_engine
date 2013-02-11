#import <Cocoa/Cocoa.h>
#include <OpenGL/OpenGL.h>

#include "fssimplewindow.h"

static int FsNormalKeyCode[256]=
{
	0,                 // 0
	0,                 // 1
	0,                 // 2
	0,                 // 3
	0,                 // 4
	0,                 // 5
	0,                 // 6
	0,                 // 7
	0,                 // 8
	FSKEY_TAB,         // 9
	0,                 // 10
	0,                 // 11
	0,                 // 12
	FSKEY_ENTER,       // 13
	0,                 // 14
	0,                 // 15
	0,                 // 16
	0,                 // 17
	0,                 // 18
	0,                 // 19
	0,                 // 20
	0,                 // 21
	0,                 // 22
	0,                 // 23
	0,                 // 24
	0,                 // 25
	0,                 // 26
	FSKEY_ESC,         // 27
	0,                 // 28
	0,                 // 29
	0,                 // 30
	0,                 // 31
	FSKEY_SPACE,       // 32
	0,                 // 33
	0,                 // 34
	0,                 // 35
	0,                 // 36
	0,                 // 37
	0,                 // 38
	FSKEY_SINGLEQUOTE, // 39
	0,                 // 40
	0,                 // 41
	0,                 // 42
	FSKEY_PLUS,        // 43
	FSKEY_COMMA,       // 44
	FSKEY_MINUS,       // 45
	FSKEY_DOT,         // 46
	FSKEY_SLASH,       // 47
	FSKEY_0,           // 48
	FSKEY_1,           // 49
	FSKEY_2,           // 50
	FSKEY_3,           // 51
	FSKEY_4,           // 52
	FSKEY_5,           // 53
	FSKEY_6,           // 54
	FSKEY_7,           // 55
	FSKEY_8,           // 56
	FSKEY_9,           // 57
	FSKEY_SEMICOLON,   // 58
	0,                 // 59
	0,                 // 60
	0,                 // 61
	0,                 // 62
	0,                 // 63
	0,                 // 64
	FSKEY_A,           // 65
	FSKEY_B,           // 66
	FSKEY_C,           // 67
	FSKEY_D,           // 68
	FSKEY_E,           // 69
	FSKEY_F,           // 70
	FSKEY_G,           // 71
	FSKEY_H,           // 72
	FSKEY_I,           // 73
	FSKEY_J,           // 74
	FSKEY_K,           // 75
	FSKEY_L,           // 76
	FSKEY_M,           // 77
	FSKEY_N,           // 78
	FSKEY_O,           // 79
	FSKEY_P,           // 80
	FSKEY_Q,           // 81
	FSKEY_R,           // 82
	FSKEY_S,           // 83
	FSKEY_T,           // 84
	FSKEY_U,           // 85
	FSKEY_V,           // 86
	FSKEY_W,           // 87
	FSKEY_X,           // 88
	FSKEY_Y,           // 89
	FSKEY_Z,           // 90
	FSKEY_LBRACKET,    // 91
	FSKEY_BACKSLASH,   // 92
	FSKEY_RBRACKET,    // 93
	0,                 // 94
	0,                 // 95
	0,                 // 96
	FSKEY_A,           // 97
	FSKEY_B,           // 98
	FSKEY_C,           // 99
	FSKEY_D,           // 100
	FSKEY_E,           // 101
	FSKEY_F,           // 102
	FSKEY_G,           // 103
	FSKEY_H,           // 104
	FSKEY_I,           // 105
	FSKEY_J,           // 106
	FSKEY_K,           // 107
	FSKEY_L,           // 108
	FSKEY_M,           // 109
	FSKEY_N,           // 110
	FSKEY_O,           // 111
	FSKEY_P,           // 112
	FSKEY_Q,           // 113
	FSKEY_R,           // 114
	FSKEY_S,           // 115
	FSKEY_T,           // 116
	FSKEY_U,           // 117
	FSKEY_V,           // 118
	FSKEY_W,           // 119
	FSKEY_X,           // 120
	FSKEY_Y,           // 121
	FSKEY_Z,           // 122
	FSKEY_LBRACKET,    // 123
	0,                 // 124
	FSKEY_RBRACKET,    // 125
	FSKEY_TILDA,       // 126
	FSKEY_BS,          // 127
	0,                 // 128
	0,                 // 129
	0,                 // 130
	0,                 // 131
	0,                 // 132
	0,                 // 133
	0,                 // 134
	0,                 // 135
	0,                 // 136
	0,                 // 137
	0,                 // 138
	0,                 // 139
	0,                 // 140
	0,                 // 141
	0,                 // 142
	0,                 // 143
	0,                 // 144
	0,                 // 145
	0,                 // 146
	0,                 // 147
	0,                 // 148
	0,                 // 149
	0,                 // 150
	0,                 // 151
	0,                 // 152
	0,                 // 153
	0,                 // 154
	0,                 // 155
	0,                 // 156
	0,                 // 157
	0,                 // 158
	0,                 // 159
	0,                 // 160
	0,                 // 161
	0,                 // 162
	0,                 // 163
	0,                 // 164
	0,                 // 165
	0,                 // 166
	0,                 // 167
	0,                 // 168
	0,                 // 169
	0,                 // 170
	0,                 // 171
	0,                 // 172
	0,                 // 173
	0,                 // 174
	0,                 // 175
	0,                 // 176
	0,                 // 177
	0,                 // 178
	0,                 // 179
	0,                 // 180
	0,                 // 181
	0,                 // 182
	0,                 // 183
	0,                 // 184
	0,                 // 185
	0,                 // 186
	0,                 // 187
	0,                 // 188
	0,                 // 189
	0,                 // 190
	0,                 // 191
	0,                 // 192
	0,                 // 193
	0,                 // 194
	0,                 // 195
	0,                 // 196
	0,                 // 197
	0,                 // 198
	0,                 // 199
	0,                 // 200
	0,                 // 201
	0,                 // 202
	0,                 // 203
	0,                 // 204
	0,                 // 205
	0,                 // 206
	0,                 // 207
	0,                 // 208
	0,                 // 209
	0,                 // 210
	0,                 // 211
	0,                 // 212
	0,                 // 213
	0,                 // 214
	0,                 // 215
	0,                 // 216
	0,                 // 217
	0,                 // 218
	0,                 // 219
	0,                 // 220
	0,                 // 221
	0,                 // 222
	0,                 // 223
	0,                 // 224
	0,                 // 225
	0,                 // 226
	0,                 // 227
	0,                 // 228
	0,                 // 229
	0,                 // 230
	0,                 // 231
	0,                 // 232
	0,                 // 233
	0,                 // 234
	0,                 // 235
	0,                 // 236
	0,                 // 237
	0,                 // 238
	0,                 // 239
	0,                 // 240
	0,                 // 241
	0,                 // 242
	0,                 // 243
	0,                 // 244
	0,                 // 245
	0,                 // 246
	0,                 // 247
	0,                 // 248
	0,                 // 249
	0,                 // 250
	0,                 // 251
	0,                 // 252
	0,                 // 253
	0,                 // 254
	0                  // 255
};

static int FsSpecialKeyCode[256]=
{
	FSKEY_UP,           // 0
	FSKEY_DOWN,         // 1
	FSKEY_LEFT,         // 2
	FSKEY_RIGHT,        // 3
	FSKEY_F1,           // 4
	FSKEY_F2,           // 5
	FSKEY_F3,           // 6
	FSKEY_F4,           // 7
	FSKEY_F5,           // 8
	FSKEY_F6,           // 9
	FSKEY_F7,           // 10
	FSKEY_F8,           // 11
	FSKEY_F9,           // 12
	FSKEY_F10,          // 13
	FSKEY_F11,          // 14
	FSKEY_F12,          // 15
	FSKEY_F1,           // 16 0x10
	FSKEY_F2,           // 17
	FSKEY_F3,           // 18
	FSKEY_F4,           // 19
	FSKEY_F5,           // 20
	FSKEY_F6,           // 21
	FSKEY_F7,           // 22
	FSKEY_F8,           // 23
	FSKEY_F9,           // 24
	FSKEY_F10,          // 25
	FSKEY_F11,          // 26
	FSKEY_F12,          // 27
	FSKEY_F1,           // 28
	FSKEY_F2,           // 29
	FSKEY_F3,           // 30
	FSKEY_F4,           // 31
	FSKEY_F5,           // 32 0x20
	FSKEY_F6,           // 33
	FSKEY_F7,           // 34
	FSKEY_F8,           // 35
	FSKEY_F9,           // 36
	FSKEY_F10,          // 37
	FSKEY_F11,          // 38
	FSKEY_INS,          // 39
	FSKEY_DEL,          // 40
	FSKEY_HOME,         // 41
	0,                  // 42 Begin
	FSKEY_END,          // 43
	FSKEY_PAGEUP,       // 44
	FSKEY_PAGEDOWN,     // 45
	FSKEY_PRINTSCRN,    // 46
	FSKEY_SCROLLLOCK,   // 47
	FSKEY_PAUSEBREAK,   // 48 0x30
	0,                  // 49
	FSKEY_PAUSEBREAK,   // 50
	0,                  // 51 Reset
	0,                  // 52 Stop
	0,                  // 53 Menu
	0,                  // 54 User
	0,                  // 55 System
	FSKEY_PRINTSCRN,    // 56
	0,                  // 57 Clear line
	0,                  // 58 Clear display
	0,                  // 59 Insert line
	0,                  // 60 Delete line
	FSKEY_INS,          // 61
	FSKEY_DEL,          // 62
	FSKEY_PAGEUP,       // 63
	FSKEY_PAGEDOWN,     // 64
	0,                  // 65 Select
	0,                  // 66 Execute
	0,                  // 67 Undo
	0,                  // 68 Redo
	0,                  // 69 Find
	0,                  // 70 Help
	0,                  // 71 Mode Switch
	0,                  // 72
	0,                  // 73
	0,                  // 74
	0,                  // 75
	0,                  // 76
	0,                  // 77
	0,                  // 78
	0,                  // 79
	0,                  // 80
	0,                  // 81
	0,                  // 82
	0,                  // 83
	0,                  // 84
	0,                  // 85
	0,                  // 86
	0,                  // 87
	0,                  // 88
	0,                  // 89
	0,                  // 90
	0,                  // 91
	0,                  // 92
	0,                  // 93
	0,                  // 94
	0,                  // 95
	0,                  // 96
	0,                  // 97
	0,                  // 98
	0,                  // 99
	0,                  // 100
	0,                  // 101
	0,                  // 102
	0,                  // 103
	0,                  // 104
	0,                  // 105
	0,                  // 106
	0,                  // 107
	0,                  // 108
	0,                  // 109
	0,                  // 110
	0,                  // 111
	0,                  // 112
	0,                  // 113
	0,                  // 114
	0,                  // 115
	0,                  // 116
	0,                  // 117
	0,                  // 118
	0,                  // 119
	0,                  // 120
	0,                  // 121
	0,                  // 122
	0,                  // 123
	0,                  // 124
	0,                  // 125
	0,                  // 126
	0,                  // 127
	0,                  // 128
	0,                  // 129
	0,                  // 130
	0,                  // 131
	0,                  // 132
	0,                  // 133
	0,                  // 134
	0,                  // 135
	0,                  // 136
	0,                  // 137
	0,                  // 138
	0,                  // 139
	0,                  // 140
	0,                  // 141
	0,                  // 142
	0,                  // 143
	0,                  // 144
	0,                  // 145
	0,                  // 146
	0,                  // 147
	0,                  // 148
	0,                  // 149
	0,                  // 150
	0,                  // 151
	0,                  // 152
	0,                  // 153
	0,                  // 154
	0,                  // 155
	0,                  // 156
	0,                  // 157
	0,                  // 158
	0,                  // 159
	0,                  // 160
	0,                  // 161
	0,                  // 162
	0,                  // 163
	0,                  // 164
	0,                  // 165
	0,                  // 166
	0,                  // 167
	0,                  // 168
	0,                  // 169
	0,                  // 170
	0,                  // 171
	0,                  // 172
	0,                  // 173
	0,                  // 174
	0,                  // 175
	0,                  // 176
	0,                  // 177
	0,                  // 178
	0,                  // 179
	0,                  // 180
	0,                  // 181
	0,                  // 182
	0,                  // 183
	0,                  // 184
	0,                  // 185
	0,                  // 186
	0,                  // 187
	0,                  // 188
	0,                  // 189
	0,                  // 190
	0,                  // 191
	0,                  // 192
	0,                  // 193
	0,                  // 194
	0,                  // 195
	0,                  // 196
	0,                  // 197
	0,                  // 198
	0,                  // 199
	0,                  // 200
	0,                  // 201
	0,                  // 202
	0,                  // 203
	0,                  // 204
	0,                  // 205
	0,                  // 206
	0,                  // 207
	0,                  // 208
	0,                  // 209
	0,                  // 210
	0,                  // 211
	0,                  // 212
	0,                  // 213
	0,                  // 214
	0,                  // 215
	0,                  // 216
	0,                  // 217
	0,                  // 218
	0,                  // 219
	0,                  // 220
	0,                  // 221
	0,                  // 222
	0,                  // 223
	0,                  // 224
	0,                  // 225
	0,                  // 226
	0,                  // 227
	0,                  // 228
	0,                  // 229
	0,                  // 230
	0,                  // 231
	0,                  // 232
	0,                  // 233
	0,                  // 234
	0,                  // 235
	0,                  // 236
	0,                  // 237
	0,                  // 238
	0,                  // 239
	0,                  // 240
	0,                  // 241
	0,                  // 242
	0,                  // 243
	0,                  // 244
	0,                  // 245
	0,                  // 246
	0,                  // 247
	0,                  // 248
	0,                  // 249
	0,                  // 250
	0,                  // 251
	0,                  // 252
	0,                  // 253
	0,                  // 254
	0                   // 255
};

static int fsKeyIsDown[FSKEY_NUM_KEYCODE]={0};

#define NKEYBUF 256


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

@interface YsMacDelegate : NSObject /* < NSApplicationDelegate > */
/* Example: Fire has the same problem no explanation */
{
}
/* - (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication; */
@end

@implementation YsMacDelegate
- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
	return YES;
}
@end



@interface YsOpenGLWindow : NSWindow
{
}

@end

@implementation YsOpenGLWindow
- (id) initWithContentRect: (NSRect)rect styleMask:(NSUInteger)wndStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)deferFlg
{
	[super initWithContentRect:rect styleMask:wndStyle backing:bufferingType defer:deferFlg];
    
	[self setAcceptsMouseMovedEvents:YES];
    
	printf("%s\n",__FUNCTION__);
	return self;
}


@end


@interface YsOpenGLView : NSOpenGLView
{
}
- (void) drawRect: (NSRect) bounds;
@end

@implementation YsOpenGLView
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


static YsOpenGLWindow *ysWnd=nil;
static YsOpenGLView *ysView=nil;


int FsIsKeyC(int code)
{
    return fsKeyIsDown[code];
}


void FsOpenWindowC(int x0,int y0,int wid,int hei)
{

    [NSApplication sharedApplication];
    [NSBundle loadNibNamed:@"MainMenu" owner:NSApp];

	YsMacDelegate *delegate;
	delegate=[YsMacDelegate alloc];
	[delegate init];
	[NSApp setDelegate: delegate];
	
	[NSApp finishLaunching];
    
    
    
	NSRect contRect;
	contRect=NSMakeRect(x0,y0,wid,hei);
	
	unsigned int winStyle=
        NSTitledWindowMask|
        NSClosableWindowMask|
        NSMiniaturizableWindowMask;
	
	ysWnd=[YsOpenGLWindow alloc];
	[ysWnd
     initWithContentRect:contRect
     styleMask:winStyle
     backing:NSBackingStoreBuffered
     defer:NO];
    
	NSOpenGLPixelFormat *format;
	NSOpenGLPixelFormatAttribute formatAttrib[]= {
     //   NSOpenGLPFAWindow,
        NSOpenGLPFADepthSize, 32,
        NSOpenGLPFAAccelerated,
     //   NSOpenGLPFAStencilSize, 32,
        NSOpenGLPFADoubleBuffer,
        NSOpenGLPFAColorSize, 32,
        0
	};
    
	format=[NSOpenGLPixelFormat alloc];
	[format initWithAttributes: formatAttrib];
	
	ysView=[YsOpenGLView alloc];
	contRect=NSMakeRect(0,0,wid,hei);
	[ysView
     initWithFrame:contRect
     pixelFormat:format];
	
	[ysWnd setContentView:ysView];
	[ysWnd makeFirstResponder:ysView];
    
	[ysWnd makeKeyAndOrderFront:nil];
	[ysWnd makeMainWindow];
    
	[NSApp activateIgnoringOtherApps:YES];
    
    glClearDepth(0.0F);
    glEnable(GL_DEPTH_TEST);
    
}

void FsSleepC(int ms)
{
	if(ms>0)
        {
		double sec;
		sec=(double)ms/1000.0;
		[NSThread sleepForTimeInterval:sec];
        }
}


void FsSwapBufferC(void)
{
	[[ysView openGLContext] flushBuffer];
}


void FsPollDeviceC(void)
{
 	NSAutoreleasePool *pool=[[NSAutoreleasePool alloc] init];
    
	while(1)
        {
	 	[pool release];
	 	pool=[[NSAutoreleasePool alloc] init];
        
		NSEvent *event;
		event=[NSApp
			   nextEventMatchingMask:NSAnyEventMask
			   untilDate: [NSDate distantPast]
			   inMode: NSDefaultRunLoopMode
			   dequeue:YES];
		if([event type]==NSRightMouseDown)
            {
		    printf("R mouse down event\n");
            }
		if(event!=nil)
            {
			[NSApp sendEvent:event];
			[NSApp updateWindows];
            }
		else
            {
			break;
            }
        }
    
	[pool release];	
}



int FsPassedTimeC(void)
{
	int ms;
    
 	NSAutoreleasePool *pool=[[NSAutoreleasePool alloc] init];
    
	static NSTimeInterval last=0.0;
	NSTimeInterval now;
    
	now=[[NSDate date] timeIntervalSince1970];
    
	NSTimeInterval passed;
	passed=now-last;
	ms=(int)(1000.0*passed);
    
	if(ms<0)
        {
		ms=1;
        }
	last=now;
    
	[pool release];	
    
	return ms;
}

