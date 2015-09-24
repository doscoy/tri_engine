
#include "core/graphics/tri_model.hpp"
#include "core/graphics/tri_vertex_types.hpp"
#include "core/kernel/memory/tri_new.hpp"
#include "shader/tri_simple3d.vsh"
#include "shader/tri_simple3d.fsh"
#include "shader/tri_model.vsh"
#include "shader/tri_model.fsh"

namespace  {


const char* SHADER_ATTR_POSITION = "a_position";
const char* SHADER_ATTR_NORMAL = "a_normal";
const char* SHADER_ATTR_UV = "a_uv";
const char* SHADER_UNIF_PMV = "u_mvp";
const char* SHADER_UNIF_COLOR_DIFFUSE = "u_diffuse";
const char* SHADER_UNIF_SHADOW_MTX = "u_shadow_mtx";
const char* SHADER_UNIF_SAMPLER = "sampler";
const char* SHADER_UNIF_SHADOW_SAMPLER = "shadow_samp";
const char* SHADER_OUT_COLOR = "FragColor";
const char* SHADER_UNIF_USE_TEXTURE_FLAG = "use_texture";
}


TRI_CORE_NS_BEGIN




Model::Model()
    : mesh_(nullptr)
    , model_shader_()
    , simple_shader_()
    , current_shader_(&model_shader_)
    , shadow_cast_(false)
    , shadow_receive_(false)
    , culling_mode_(cross::RenderSystem::CullingMode::MODE_BACK)
{

    //  シェーダ作成
    model_shader_.build(model_vsh, model_fsh);
    simple_shader_.build(simple3d_vsh, simple3d_fsh);
}


Model::~Model() {


}



void Model::render(const RenderInfo& info) {

    if (info.renderMode() == RenderInfo::SHADOW) {
        if (!shadow_cast_) {
            return;
        }
        current_shader_ = &simple_shader_;
    } else {
        current_shader_ = &model_shader_;
    }

    auto& meshes = mesh_->meshes();
    for (int i = 0; i < meshes.size(); ++i) {
    
        auto& mesh = meshes.at(i);

        cross::RenderSystem::resetBufferBind();
        mesh->bind();

        current_shader_->use();
        current_shader_->setUniform(SHADER_UNIF_PMV, *info.transform());
        current_shader_->setUniform(SHADER_UNIF_SAMPLER, 0);
        current_shader_->setUniform(SHADER_UNIF_SHADOW_SAMPLER, 1);
        bool draw_flag = info.renderMode() == RenderInfo::SHADOW ? false : true;

        //  シェーダに描画フラグ設定
        current_shader_->setUniform("draw_flag", draw_flag);
        current_shader_->setUniform("draw_shadow", shadow_receive_);
        
        //  影用行列生成
        Mtx44 shadow_bias;
        Mtx44::makeShadowBias(shadow_bias);

        Mtx44 shadow_mtx;
        shadow_mtx = shadow_bias * info.projMatrix()* info.lightMatrix();
        
        current_shader_->setUniform(SHADER_UNIF_SHADOW_MTX, shadow_mtx);
        
        //  頂点設定
        current_shader_->bindAttributeLocation(0, SHADER_ATTR_POSITION);

        //  法線設定
        current_shader_->bindAttributeLocation(1, SHADER_ATTR_NORMAL);

        //  UV設定
        current_shader_->bindAttributeLocation(2, SHADER_ATTR_UV);

        //  出力カラー設定
        current_shader_->bindFragmentDataLocation(0, SHADER_OUT_COLOR);



        auto& material = mesh->material();
        if (material) {
            //  マテリアルを持っているので設定
            auto& model_texture = material->diffuseMap();

            //  テクスチャを設定
            if (model_texture) {
                cross::RenderSystem::setActiveTextureUnit(
                    cross::RenderSystem::TextureUnit::UNIT0
                );
                model_texture->bind();
                current_shader_->setUniform(SHADER_UNIF_USE_TEXTURE_FLAG, true);

            } else {
                current_shader_->setUniform(SHADER_UNIF_USE_TEXTURE_FLAG, false);
            }
            
            //  カラー設定
            const auto& diffuse = material->diffuse();
            current_shader_->setUniform(SHADER_UNIF_COLOR_DIFFUSE, diffuse.redFloat(), diffuse.greenFloat(), diffuse.blueFloat(), diffuse.alphaFloat());
        }

        cross::RenderSystem::setActiveTextureUnit(
            cross::RenderSystem::TextureUnit::UNIT1
        );
        auto& shadow_texture = info.shadowTexture();
        if (shadow_texture) {
            shadow_texture->bind();
        }



        cross::RenderSystem::setCullingMode(culling_mode_);

        cross::RenderSystem::drawElements(
            cross::RenderSystem::DrawMode::MODE_TRIANGLES,
            mesh->indexCount(),
            sizeof(uint32_t)
        );
        mesh->unbind();
    }
}


//  モデル生成関数
ModelPtr Model::create() {
    ModelPtr m(T3_NEW Model);
    return m;
}

ModelPtr Model::create(
    const FilePath& mesh_path
) {
    MeshPtr mesh = Mesh::create(mesh_path);
    ModelPtr m(T3_NEW Model);
    m->mesh(mesh);
    return m;
}



TRI_CORE_NS_END

