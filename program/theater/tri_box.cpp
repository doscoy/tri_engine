#include "tri_box.hpp"
#include "../gfx/tri_camera.hpp"

namespace t3 {
inline namespace theater {


void Box::render()
{
    ogl::matrixMode(GL_MODELVIEW);
    const Mtx4* transform = getTransformMatrix();
    ogl::loadMatrixf(transform->pointer());
    
    

}


}   // namespace theater
}   // namespace t3