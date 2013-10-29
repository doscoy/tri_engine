#ifndef PLATFORM_OPENGL_WRAPPER_HPP_INCLUDED
#define PLATFORM_OPENGL_WRAPPER_HPP_INCLUDED


#include <OpenGL/gl.h>
#include <OpenGL/glu.h>




namespace ogl {


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
    ogl::clear(flag);
}




}   // namespace ogl;



#endif // PLATFORM_OPENGL_WRAPPER_HPP_INCLUDED