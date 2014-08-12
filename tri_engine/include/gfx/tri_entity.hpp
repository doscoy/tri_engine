#ifndef TRI_ENTITY_HPP_INCLUDED
#define TRI_ENTITY_HPP_INCLUDED

#include "math/tri_matrix.hpp"


namespace t3 {
inline namespace gfx {


class Entity
{
protected:
    Entity(){};
    virtual ~Entity(){};
    
public:
    virtual bool isRenderable() const {
        return false;
    }
    
    virtual void render(const Mtx44&){}
};


}   // namespace gfx
}   // namespace t3


#endif // TRI_ENTITY_HPP_INCLUDED