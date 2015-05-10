
#ifndef TRI_RESOURCE_HPP_INCLUDED
#define TRI_RESOURCE_HPP_INCLUDED

//  include
#include "util/tri_uncopyable.hpp"
#include "util/tri_unique_id.hpp"
#include "kernel/tri_kernel.hpp"


constexpr int RESOURCE_NAME_SIZE = 96;  ///< リソース名の長さ限界

namespace t3 {

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


}   // namespace t3

#endif // TRI_RESOURCE_HPP_INCLUDED
