#ifndef TRI_MODEL_HPP_INCLUDED
#define TRI_MODEL_HPP_INCLUDED


#include "tri_entity.hpp"
#include "tri_mesh.hpp"
#include "tri_shader.hpp"


namespace t3 {


class Model
    : public Entity
{
public:
    Model();
    ~Model();
    
public:
    bool isRenderable() const override {
        return mesh_ != 0;
    }
    
    void render(const Mtx44& transform) override;

    void mesh(Mesh* mesh) {
        mesh_ = mesh;
    }


private:
    Mesh* mesh_;
    Shader default_shader_;
    Shader* current_shader_;
};



}   // namespace t3


#endif // TRI_COLOR_HPP_INCLUDED