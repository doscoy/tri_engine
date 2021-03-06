////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_resource_manager.hpp
    リソースマネージャ.
*/
#ifndef TRI_RESOURCE_MANAGER_HPP_INCLUDED
#define TRI_RESOURCE_MANAGER_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include <list>
#include "../utility/tri_singleton.hpp"
#include "../utility/tri_unique_id.hpp"
#include "../debug/tri_assert.hpp"
#include "../base/tri_resource.hpp"
#include "../utility/tri_string_util.hpp"


TRI_CORE_NS_BEGIN


///
/// リソースマネージャ
template <typename ResourceType>
class ResourceManager
    : public Singleton<ResourceManager<ResourceType>>
{
    friend class Singleton<ResourceManager<ResourceType>>;

    using Resources = List<SharedPtr<ResourceType>>;

    
protected:
    
    ///
    /// コンストラクタ
    ResourceManager() = default;
    
    ///
    /// デストラクタ
    ~ResourceManager() = default;

public:
    ///
    ///  ロード
    UniqueID load(
        const String& name
    ){
        auto res = findResource(name);
        if (res) {
            return res->resourceID();
        }
        
        //  無かったので読み込み
        FilePath path(name);
        res = ResourceType::create(path);
        T3_NULL_ASSERT(res);

        //  追加
        resources_.push_back(res);
        
        return res->resourceID();
    }

    ///
    ///  プリロード
    void prepare(
        const t3::File& file
    ) {
        auto res = findResource(file.name());
        if (res) {
            //  同名のリソースが既に登録されている
            return;
        }
        
        res = ResourceType::create(file);
        T3_NULL_ASSERT(res);

        //  追加
        resources_.push_back(res);
        
    }
    
    //  リソースを取得
    const SharedPtr<ResourceType> findResource(
        String name
    ){
        for (auto& res : resources_) {

            if (res->resourceName() == name) {
                return res;
            }
        }
      
        return nullptr;
    }
    ///
    ///  リソースを取得
    const SharedPtr<ResourceType> findResource(
        const UniqueID id
    ){
        typename Resources::iterator end = resources_.end();
        for( typename Resources::iterator it = resources_.begin(); it != end; ++it){
            
            if ((*it)->resourceID() == id) {
                return (*it);
            }
        }
        
        return 0;
    }

    ///
    /// 管理リソースを取得
    auto& resources() {
        return resources_;
    }

    ///
    /// 管理リソースを取得
    const auto& resources() const {
        return resources_;
    }

private:
    Resources resources_;   ///< 管理リソース

};


TRI_CORE_NS_END

#endif // TRI_RESOURCE_MANAGER_HPP_INCLUDED
