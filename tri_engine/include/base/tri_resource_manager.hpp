#ifndef TRI_RESOURCE_MANAGER_HPP_INCLUDED
#define TRI_RESOURCE_MANAGER_HPP_INCLUDED

#include <list>
#include "../util/tri_singleton.hpp"
#include "../util/tri_unique_id.hpp"
#include "../dbg/tri_dbg.hpp"
#include "../base/tri_resource.hpp"



namespace t3 {
    


    
template <typename ResourceType>
class ResourceManager
    : public Singleton<ResourceManager<ResourceType>>
{
    friend class Singleton<ResourceManager<ResourceType>>;

    typedef std::list<std::shared_ptr<ResourceType>> Resources;

    
protected:
    ResourceManager() = default;
    ~ResourceManager() = default;

public:
    
    // *********************************************
    //  ロード
    uid_t load(
        const FilePath& path
    ){
        for (auto res : resources_) {
            if (std::strncmp(res->getResourceName(), path.getFullPath().c_str(), RESOURCE_NAME_SIZE) == 0) {
                //  既に読み込み済
                return res->getResourceID();
            }
        }
    
    
    
    
        std::shared_ptr<ResourceType> res = ResourceType::create(path);
        T3_NULL_ASSERT(res);
        resources_.push_back(res);
        
        return res->getResourceID();
    }
    
    
    // *********************************************
    //  リソースを取得
    const std::shared_ptr<ResourceType> getResource(
        std::string name
    ){
        
      
        typename Resources::iterator end = resources_.end();
        for (typename Resources::iterator it = resources_.begin(); it != end; ++it) {
            if (strcmp((*it)->getName(), name.c_str())) {
                return (*it);
            }
        }
      
        return nullptr;
    }
    
    // *********************************************
    //  リソースを取得
    const std::shared_ptr<ResourceType> getResource(
        const uid_t id
    ){
        typename Resources::iterator end = resources_.end();
        for( typename Resources::iterator it = resources_.begin(); it != end; ++it){
            
            if ( (*it)->getResourceID() == id ){
                return (*it);
            }
        }
        
        return 0;
    }

private:
    Resources resources_;

};

    

    
    
    
}   // namespace t3

#endif // TRI_RESOURCE_MANAGER_HPP_INCLUDED
