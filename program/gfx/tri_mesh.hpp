#ifndef TRI_MESH_HPP_INCLUDED
#define TRI_MESH_HPP_INCLUDED


namespace t3 {
inline namespace gfx {


typedef float vec[3];
typedef unsigned int idx[3];

class Mesh
{
    unsigned int vertex_count_;
    unsigned int face_count_;
    vec* vert_;
    vec* normal_;
    vec* fnormal_;
    idx* face_;
    unsigned int buffers_[3];

public:
    Mesh(char *);
    virtual ~Mesh();
    
public:
    void draw(void);
};

} // inline namespace gfx
} // namespace t3

#endif // TRI_MESH_HPP_INCLUDED

