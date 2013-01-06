#ifndef TRI_RESOURCE_MANAGER_HPP_INCLUDED
#define TRI_RESOURCE_MANAGER_HPP_INCLUDED

#include <list>
#include "../util/tri_singleton.hpp"
#include "../util/tri_unique_id.hpp"
#include "../dbg/tri_dbg.hpp"
#include "../kernel/tri_resource.hpp"
#include "../gfx/tri_texture_factory.hpp"
#include "../gfx/tri_texture.hpp"




namespace t3 {
    


    
template <typename ResourceType>
class ResourceManager
    : public Singleton< ResourceManager<ResourceType> >
{
    friend class Singleton< ResourceManager<ResourceType> >;

public:
    typedef std::list<Resource*> Resources;

    
protected:
    ResourceManager() = default;
    ~ResourceManager() = default;

public:
    
    // *********************************************
    //  ロード
    uid_t load(
        const char* const path 
    ){
        ResourceType* res = ResourceType::create( path );
        T3_NULL_ASSERT( res );
        resources_.push_back( res );
        
        return res->getID();
    }
    
    
    // *********************************************
    //  リソースを取得
    const ResourceType* getResource(
        const char* const name
    ){
        
      
        Resources::iterator end = resources_.end();
        for ( Resources::iterator it = resources_.begin(); it != end; ++it ){
            if ( strcmp((*it)->getName(), name ) ){
                return *it;
            }
        }
      
        return nullptr;
    }
    
    // *********************************************
    //  リソースを取得
    const ResourceType* getResource(
        const uid_t id
    ){
      
        for ( auto res: resources_ ) {
            
            if ( res->getID() == id ){
                return static_cast<ResourceType*>( res );
            }
        }
        
        return nullptr;
    }

private:
    Resources resources_;

};

    
typedef ResourceManager<Texture> TextureManager;

    
    
    
}   // namespace t3

#endif // TRI_RESOURCE_MANAGER_HPP_INCLUDED
