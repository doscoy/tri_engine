#ifndef TRI_ENTITY_HPP_INCLUDED
#define TRI_ENTITY_HPP_INCLUDED


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
    
    virtual void render(){}
};


}   // namespace gfx
}   // namespace t3


#endif // TRI_ENTITY_HPP_INCLUDED