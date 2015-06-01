

#include "gfx/tri_material.hpp"

namespace t3 {


void Material::load(const char *const file_path) {
    FileStream file(file_path, std::ios::in | std::ios::binary);
    char buf[1024];
    
    
    T3_ASSERT_MSG(file, "%s is not found.", file_path);
    
    while (file.getline(buf, sizeof buf)) {
        //  ファイルを順番に読んでいって情報を拾う
        //--------------------------------
        //  マテリアル名
        if (buf[0] == 'n'
            && buf[1] == 'e'
        ) {
            //  newmtl マテリアル名
            char newmtl[128];
            sscanf(buf, "%*s %s", newmtl);
            material_name_ = newmtl;

        //---------------------------------
        //  テクスチャ
        } else if (buf[0] == 'm'
            && buf[1] == 'a'
        ) {
            //  map_Kd
            char map_Kd[128];
            sscanf(buf, "%*s %s", map_Kd);
            FilePath tex_path = String(map_Kd);
            texture_ = Texture::create(tex_path);
            
        //---------------------------------
        //  アンビエント
        } else if (buf[0] == 'K'
            && buf[1] == 'a'
        ) {
            //  Ka
            float r,g,b;
            sscanf(buf, "%*s %f %f %f", &r, &g, &b);
            ambient_.redFloat(r);
            ambient_.redFloat(g);
            ambient_.redFloat(b);
            ambient_.alphaFloat(1.0f);
        
        //---------------------------------
        //  ディフューズ
        } else if (buf[0] == 'K'
            && buf[1] == 'd'
        ) {
            //  Ka
            float r,g,b;
            sscanf(buf, "%*s %f %f %f", &r, &g, &b);
            diffuse_.redFloat(r);
            diffuse_.redFloat(g);
            diffuse_.redFloat(b);
            diffuse_.alphaFloat(1.0f);
        
        //---------------------------------
        //  スペキュラ
        } else if (buf[0] == 'K'
            && buf[1] == 's'
        ) {
            //  Ka
            float r,g,b;
            sscanf(buf, "%*s %f %f %f", &r, &g, &b);
            specular_.redFloat(r);
            specular_.redFloat(g);
            specular_.redFloat(b);
            specular_.alphaFloat(1.0f);
        }
        
    }

}


MaterialPtr Material::create() {
    MaterialPtr p(T3_NEW Material);
    return p;
}

MaterialPtr Material::create(const char *const material_file_path) {
    MaterialPtr p(T3_NEW Material);
    p->load(material_file_path);
    return p;
}


}   //  namespace t3

