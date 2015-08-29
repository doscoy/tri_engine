#include "core/graphics/tri_dae_loader.hpp"
#include "core/graphics/tri_vertex_types.hpp"
#include "../../third_party/tiny_collada/tiny_collada_parser.hpp"



TRI_CORE_NS_BEGIN



SubMeshDataPtr DaeLoader::load(
    const char* const path
) {
    tinycollada::Parser parser;
    parser.parse(path);

    const auto& scenes = parser.scenes();
    for (const auto& s : scenes) {
        
    
    }

    SubMeshDataPtr submesh = std::make_shared<SubMeshData>();
  

    

    return submesh;
}

TRI_CORE_NS_END

