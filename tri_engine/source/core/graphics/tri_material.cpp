

#include "core/graphics/tri_material.hpp"

TRI_CORE_NS_BEGIN

MaterialPtr Material::create() {
    MaterialPtr p;
    p.reset(T3_NEW Material());
    return p;
}


TRI_CORE_NS_END

