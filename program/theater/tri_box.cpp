#include "tri_box.hpp"
#include "../gfx/tri_camera.hpp"

namespace t3 {
inline namespace theater {


void Box::render()
{
    glMatrixMode(GL_MODELVIEW);
    Mtx4 view;
    Camera cam;
    cam.getViewMatrix( view );
    glLoadMatrixf( view.pointer() );


}


}   // namespace theater
}   // namespace t3