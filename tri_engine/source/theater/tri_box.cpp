#include "tri_box.hpp"
#include "gfx/tri_camera.hpp"
#include "gfx/tri_render_system.hpp"
#include "kernel/tri_kernel.hpp"

namespace t3 {
inline namespace theater {


void Box::render()
{
    const Mtx4* transform = getTransformMatrix();
    t3::RenderSystem::setWorldTransformMatrix(*transform);
}


}   // namespace theater
}   // namespace t3