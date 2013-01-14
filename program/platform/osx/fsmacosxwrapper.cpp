#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

extern "C" void FsOpenWindowC(int x0,int y0,int wid,int hei,int useDoubleBuffer);
extern "C" void FsSwapBufferC(void);
extern "C" void FsSleepC(int ms);
extern "C" void FsPollDeviceC(void);
extern "C" int FsInkeyC(void);
extern "C" int FsIsKeyC(int code);
extern "C" int FsPassedTimeC();

void FsOpenWindow(int x0,int y0,int wid,int hei,int useDoubleBuffer)
{
	FsOpenWindowC(x0,y0,wid,hei,useDoubleBuffer);
}

void FsSwapBuffers(void)
{
    FsSwapBufferC();
}

void FsSleep(int ms)
{
    FsSleepC(ms);
}

void FsPollDevice(void)
{
    FsPollDeviceC();
}


int FsInkey()
{
    return FsInkeyC();
}

int FsIsKey(int code)
{
    return FsIsKeyC(code);
}

int FsPassedTime()
{
    return FsPassedTimeC();
}