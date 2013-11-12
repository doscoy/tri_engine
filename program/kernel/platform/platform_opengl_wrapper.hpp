#ifndef PLATFORM_OPENGL_WRAPPER_HPP_INCLUDED
#define PLATFORM_OPENGL_WRAPPER_HPP_INCLUDED


#include <OpenGL/gl.h>
#include <OpenGL/glu.h>




namespace ogl {


enum ColorFormat
{
    RGBA = GL_RGBA,
    RGB  = GL_RGB,
};



inline void cullFace(
    int mode
) {
    glCullFace(mode);
}

inline void depthMask(
    bool flag
) {
    glDepthMask(flag);
}
inline void clearDepth(
    const float val
) {
    glClearDepth(val);
}

inline void enable(
    const int flag
) {
    glEnable(flag);
}

inline void disable(
    const int flag
) {
    glDisable(flag);
}

inline void normal3d(
    double x,
    double y,
    double z
) {
    glNormal3d(x, y, z);
}

inline void materialfv(
    int face,
    int pname,
    float* param
) {
    glMaterialfv(face, pname, param);
}

inline void clear(
    const int flag
) {
    glClear(flag);
}

inline void clearColor(
    float r,
    float g,
    float b,
    float a
) {
    glClearColor(r, g, b, a);
}

inline void pushMatrix()
{
    glPushMatrix();
}

inline void popMatrix()
{
    glPopMatrix();
}

inline void depthFunc(
    const int flag
) {
    glDepthFunc(flag);
}

inline void blendFunc(
    int sfactor,
    int dfactor
) {
    glBlendFunc(sfactor, dfactor);
}


inline void pixelStorei(
    int pname,
    int param
) {
    glPixelStorei(pname, param);
}

inline void texParameteri(
    int target,
    int pname,
    int param
) {
    glTexParameteri(target, pname, param);
}

inline void matrixMode(
    int mode
) {
    glMatrixMode(mode);
}

inline void ortho(
    double left,
    double right,
    double bottom,
    double top,
    double znear,
    double zfar
) {

    glOrtho(left, right, bottom, top, znear, zfar);
}


inline void loadIdentity()
{
    glLoadIdentity();
}

inline void texImage2d(
    int target,
    int level,
    int internalformat,
    int width,
    int height,
    int border,
    int format,
    int type,
    const void* pixels
){
    glTexImage2D(
        target,
        level,
        internalformat,
        width,
        height,
        border,
        format,
        type,
        pixels
    );
}

inline void begin(
    int mode
) {
    glBegin(mode);
}

inline void end()
{
    glEnd();
}

inline void vertex2f(
    float x,
    float y
) {
    glVertex2f(x, y);
}


inline void vertex3f(
    float x,
    float y,
    float z
) {
    glVertex3f(x, y, z);
}

inline void normal3fv(
    const float* const nv
) {
    glNormal3fv(nv);
}

inline void color4ub(
    int r,
    int g,
    int b,
    int a
) {
    glColor4ub(r, g, b, a);
}

inline void viewport(
    int x,
    int y,
    int w,
    int h
){
    glViewport(x, y, w, h);
}

inline void shadeModel(
    int mode
) {
    glShadeModel(mode);
}

inline void loadMatrixf(
    const float* const mtx
) {
    glLoadMatrixf(mtx);
}

inline void drawElements(
    int mode,
    int count,
    int type,
    const void* indices
){
    glDrawElements(mode, count, type, indices);
}

inline void bindBuffer(
    int target,
    int buffer
){
    glBindBuffer(target, buffer);
}

inline void enableClientState(
    int array
){
    glEnableClientState(array);
}


inline void disableClientState(
    int array
){
    glDisableClientState(array);
}

inline void genFramebuffers(
    int num,
    uint32_t* buffer
){
    glGenFramebuffers(num, buffer);
}

inline void bindFramebuffer(
    int target,
    uint32_t buffer
) {
    glBindFramebuffer(target, buffer);
}

inline void deleteFramebuffers(
    const int num,
    uint32_t* buffer
) {
    glDeleteFramebuffers(num, buffer);
}

inline int checkFramebufferStatus(int target) {
    return glCheckFramebufferStatusEXT(target);
}


inline void genRenderbuffers(
    int num,
    uint32_t* buffer
) {
    glGenRenderbuffers(num, buffer);
}


inline void bindRenderbuffer(
    int target,
    uint32_t buffer
) {
    glBindRenderbuffer(target, buffer);
}


inline void deleteRenderbuffers(
    const int num,
    uint32_t* buffer
) {
    glDeleteRenderbuffers(num, buffer);
}


inline void framebufferRenderbuffer(
    int target,
    int attachment,
    int renderbuffertarget,
    int renderbuffer
) {
    glFramebufferRenderbuffer(
        target,
        attachment,
        renderbuffertarget,
        renderbuffer
    );
}

inline void renderbufferStorage(
    int target,
    int internalformat,
    int width,
    int height
) {
    glRenderbufferStorage(
        target,
        internalformat,
        width,
        height
    );
}

inline void genBuffers(
    int num,
    uint32_t* buffers
){
    glGenBuffers(num, buffers);
}

inline void deleteBuffers(
    int num,
    uint32_t* buffers
) {
    glDeleteBuffers(num, buffers);
}

inline void bufferData(
    int target,
    int size,
    const void* data,
    int usage
) {
    glBufferData(target, size, data, usage);
}

inline void bufferSubData(
    int target,
    int offset,
    int size,
    const void* data
) {
    glBufferSubData(
        target,
        offset,
        size,
        data
    );
}

inline void vertexPointer(
    int size,
    int type,
    int stride,
    const GLvoid *pointer
) {
    glVertexPointer(size, type, stride, pointer);
}


inline void normalPointer(
    int type,
    int stride,
    const void* pointer
) {
    glNormalPointer(type, stride, pointer);
}

inline void colorPointer(
    int size,
    int type,
    int stride,
    const void* pointer
) {
    glColorPointer(size, type, stride, pointer);
}

inline void texCoordPointer(
    int size,
    int type,
    int stride,
    const void* pointer
) {
    glTexCoordPointer(size, type, stride, pointer);
}

inline void texCoord2f(
    float u,
    float v
) {
    glTexCoord2f(u, v);
}




}   // namespace ogl;



#endif // PLATFORM_OPENGL_WRAPPER_HPP_INCLUDED