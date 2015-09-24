#include "core/graphics/tri_mtl_loader.hpp"


TRI_CORE_NS_BEGIN

MaterialPtr
MtlLoader::load(
    const char* const path
) {


    FileStream file(path, std::ios::in | std::ios::binary);
    char buf[1024];
    
    
    T3_ASSERT_MSG(file, "%s is not found.", path);
    
    MaterialPtr material = Material::create();

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

            //  マテリアル名設定
            material->name(newmtl);

        //---------------------------------
        //  テクスチャ
        } else if (buf[0] == 'm'
            && buf[1] == 'a'
        ) {
            //  map_Kd
            char map_Kd[128];
            sscanf(buf, "%*s %s", map_Kd);
            FilePath tex_path = String(map_Kd);
            auto t = Texture::create(tex_path);

            //  テクスチャ設定
            material->diffuseMap(t);

        //---------------------------------
        //  アンビエント
        } else if (buf[0] == 'K'
            && buf[1] == 'a'
        ) {
            //  Ka
            float r,g,b;
            sscanf(buf, "%*s %f %f %f", &r, &g, &b);
            Color c;
            c.redFloat(r);
            c.redFloat(g);
            c.redFloat(b);
            c.alphaFloat(1.0f);

            material->ambient(c);
        
        //---------------------------------
        //  ディフューズ
        } else if (buf[0] == 'K'
            && buf[1] == 'd'
        ) {
            //  Ka
            float r,g,b;
            sscanf(buf, "%*s %f %f %f", &r, &g, &b);
            Color c;
            c.redFloat(r);
            c.redFloat(g);
            c.redFloat(b);
            c.alphaFloat(1.0f);
        
            material->diffuse(c);

        //---------------------------------
        //  スペキュラ
        } else if (buf[0] == 'K'
            && buf[1] == 's'
        ) {
            //  Ka
            float r,g,b;
            sscanf(buf, "%*s %f %f %f", &r, &g, &b);
            Color c;
            c.redFloat(r);
            c.redFloat(g);
            c.redFloat(b);
            c.alphaFloat(1.0f);

            material->specular(c);
        }
        
    }

    return material;
}



TRI_CORE_NS_END


