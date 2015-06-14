/**
    @file tri_resource.hpp
    リソース.
*/

#ifndef TRI_RESOURCE_HPP_INCLUDED
#define TRI_RESOURCE_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "core/utility/tri_unique_id.hpp"
#include "core/kernel/tri_kernel.hpp"

TRI_CORE_NS_BEGIN

constexpr int RESOURCE_NAME_SIZE = 96;  ///< リソース名の長さ限界

///
/// リソースクラス
class Resource
    : private Uncopyable
{
public:
    ///
    /// コンストラクタ
    Resource();
    
    ///
    /// コンストラクタ
    Resource(const char* const name);
    
    ///
    /// デストラクタ
    virtual ~Resource(){}
    
public:
    ///
    /// リソース名設定
    void resourceName(const char* const name){
        std::strncpy(
            resource_name_,
            name,
            RESOURCE_NAME_SIZE
        );
    }
    
    ///
    /// リソース名取得
    const char* resourceName() const {
        return resource_name_;
    }
    
    ///
    /// リソースID取得
    UniqueID resourceID() const {
        return resource_id_;
    }
    
private:
    UniqueID resource_id_;                      ///< リソースUD
    char resource_name_[RESOURCE_NAME_SIZE];    ///< リソース名
};


TRI_CORE_NS_END

#endif // TRI_RESOURCE_HPP_INCLUDED
