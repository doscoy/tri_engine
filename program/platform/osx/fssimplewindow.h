#ifndef FSSIMPLEWINDOW_IS_INCLUDED
#define FSSIMPLEWINDOW_IS_INCLUDED



#ifdef __cplusplus
// This needs to be included from Objective-C code for mouse-event enums.
// C++ specific declaration must be enclosed by #ifdef __cplucplus and #endif

void FsOpenWindow(int x0,int y0,int wid,int hei);
void FsSwapBuffers(void);
void FsSleep(int ms);
void FsPollDevice(void);
int FsIsKey(int code);
int FsPassedTime();


#endif // << #ifdef __cplusplus


#endif
