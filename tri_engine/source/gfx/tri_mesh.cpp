//
//  obj_mesh.cpp
//  tri_sandbox_osx
//
//  Created by KANI Tetsuro on 2013/02/04.
//  Copyright (c) 2013年 KANI Tetsuro. All rights reserved.
//

#include "tri_mesh.hpp"
#include "dbg/tri_assert.hpp"
#include <fstream>
#include "platform/platform_sdk.hpp"
#include "geometry/tri_aabb.hpp"


namespace t3 {
inline namespace gfx {

#define BUFFER_OFFSET(bytes) ((GLubyte *)nullptr + (bytes))



Mesh::Mesh(
    const char* const name
)   : vertex_count_(0)
    , face_count_(0)
    , vert_(nullptr)
    , normal_(nullptr)
    , fnormal_(nullptr)
    , face_(nullptr)
    , buffers_()
    , sphere_()
{
    std::ifstream file(name, std::ios::in | std::ios::binary);
    char buf[1024];
    int i;
    int v;
    int f;
    
    
    T3_ASSERT(file);
    
    v = f = 0;
    //  obj解析
    while (file.getline(buf, sizeof buf)) {
        //  行頭がvだったら頂点
        if (buf[0] == 'v' && buf[1] == ' ') {
            ++v;
        }
        //  fだったら面
        else if (buf[0] == 'f' && buf[1] == ' ') {
            ++f;
        }
    }
    
    vertex_count_ = v;
    face_count_ = f;
    

    vert_ = new vertex_t[v];
    T3_NULL_ASSERT(vert_);
    normal_ = new vertex_t[v];
    T3_NULL_ASSERT(normal_);
    fnormal_ = new vertex_t[f];
    T3_NULL_ASSERT(fnormal_);
    face_ = new index_t[f];
    T3_NULL_ASSERT(face_);

    
    
    file.clear();
    file.seekg(0L, std::ios::beg);
    
    
    v = f = 0;
    AABB aabb;
    while (file.getline(buf, sizeof buf)) {
        if (buf[0] == 'v' && buf[1] == ' ') {
            sscanf(buf, "%*s %f %f %f", vert_[v], vert_[v] + 1, vert_[v] + 2);

            Vec3 new_point;
            new_point.x_ = vert_[v][0];
            new_point.y_ = vert_[v][1];
            new_point.z_ = vert_[v][2];

            aabb.addPoint(new_point);
            ++v;
        }
        else if (buf[0] == 'f' && buf[1] == ' ') {
            if (sscanf(buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", face_[f], face_[f] + 1, face_[f] + 2) != 3) {
                if (sscanf(buf + 2, "%d//%*d %d//%*d %d//%*d", face_[f], face_[f] + 1, face_[f] + 2) != 3) {
                    sscanf(buf + 2, "%d %d %d", face_[f], face_[f] + 1, face_[f] + 2);
                }
            }
            --face_[f][0];
            --face_[f][1];
            --face_[f][2];
            ++f;
        }
    }
    
    //  aabbをもとに境界球作成
    Vec3 radius;
    Vec3 center;
    aabb.getCenter(&center);
    aabb.getRadius(&radius);
    
    float sphere_radius = radius.x_;
    if (sphere_radius < radius.y_) {
        sphere_radius = radius.y_;
    }
    if (sphere_radius < radius.z_) {
        sphere_radius = radius.z_;
    }
    
    sphere_.setPosition(center);
    sphere_.setRadius(sphere_radius);

    for (i = 0; i < f; ++i) {
        float dx1 = vert_[face_[i][1]][0] - vert_[face_[i][0]][0];
        float dy1 = vert_[face_[i][1]][1] - vert_[face_[i][0]][1];
        float dz1 = vert_[face_[i][1]][2] - vert_[face_[i][0]][2];
        float dx2 = vert_[face_[i][2]][0] - vert_[face_[i][0]][0];
        float dy2 = vert_[face_[i][2]][1] - vert_[face_[i][0]][1];
        float dz2 = vert_[face_[i][2]][2] - vert_[face_[i][0]][2];
        
        fnormal_[i][0] = dy1 * dz2 - dz1 * dy2;
        fnormal_[i][1] = dz1 * dx2 - dx1 * dz2;
        fnormal_[i][2] = dx1 * dy2 - dy1 * dx2;
    }
    

    for (i = 0; i < v; ++i) {
        normal_[i][0] = normal_[i][1] = normal_[i][2] = 0.0;
    }
    
    for (i = 0; i < f; ++i) {
        normal_[face_[i][0]][0] += fnormal_[i][0];
        normal_[face_[i][0]][1] += fnormal_[i][1];
        normal_[face_[i][0]][2] += fnormal_[i][2];
        
        normal_[face_[i][1]][0] += fnormal_[i][0];
        normal_[face_[i][1]][1] += fnormal_[i][1];
        normal_[face_[i][1]][2] += fnormal_[i][2];
        
        normal_[face_[i][2]][0] += fnormal_[i][0];
        normal_[face_[i][2]][1] += fnormal_[i][1];
        normal_[face_[i][2]][2] += fnormal_[i][2];
    }
    
    for (i = 0; i < v; ++i) {
        float a = sqrt(normal_[i][0] * normal_[i][0]
                       + normal_[i][1] * normal_[i][1]
                       + normal_[i][2] * normal_[i][2]);
        
        if (a != 0.0) {
            normal_[i][0] /= a;
            normal_[i][1] /= a;
            normal_[i][2] /= a;
        }
    }
    
    ogl::genBuffers(
        3,
        buffers_
    );
    
    ogl::bindBuffer(
        GL_ARRAY_BUFFER,
        buffers_[0]
    );
    ogl::bufferData(
        GL_ARRAY_BUFFER,
        vertex_count_ * sizeof(vertex_t),
        vert_,
        GL_STATIC_DRAW
    );
    
    ogl::bindBuffer(
        GL_ARRAY_BUFFER,
        buffers_[1]
    );
    ogl::bufferData(
        GL_ARRAY_BUFFER,
        vertex_count_ * sizeof(vertex_t),
        normal_,
        GL_STATIC_DRAW
    );
    
    ogl::bindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        buffers_[2]
    );
    ogl::bufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        face_count_ * sizeof(index_t),
        face_,
        GL_STATIC_DRAW
    );
}


Mesh::~Mesh()
{
    delete[] vert_;
    delete[] normal_;
    delete[] fnormal_;
    delete[] face_;
    
    ogl::deleteBuffers(3, buffers_);
}


void Mesh::draw(void)
{

    ogl::enableClientState(GL_VERTEX_ARRAY);
    ogl::enableClientState(GL_NORMAL_ARRAY);
    

    ogl::bindBuffer(GL_ARRAY_BUFFER, buffers_[0]);
    ogl::vertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));
    

    ogl::bindBuffer(GL_ARRAY_BUFFER, buffers_[1]);
    ogl::normalPointer(GL_FLOAT, 0, BUFFER_OFFSET(0));
    

    ogl::bindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers_[2]);
    ogl::drawElements(
        GL_TRIANGLES,
        face_count_ * 3,
        GL_UNSIGNED_INT,
        BUFFER_OFFSET(0)
    );
    

    ogl::disableClientState(GL_VERTEX_ARRAY);
    ogl::disableClientState(GL_NORMAL_ARRAY);
}

} // inline namespace gfx
} // namespace t3
