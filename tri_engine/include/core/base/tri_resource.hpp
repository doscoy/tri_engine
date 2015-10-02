////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
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


///
/// リソースクラス
class Resource
    : private Uncopyable
{
public:
    ///
    /// コンストラクタ
    Resource()
        : resource_id_()
        , resource_name_()
    {}
    
    ///
    /// デストラクタ
    virtual ~Resource(){}
    
public:
    ///
    /// リソース名設定
    void resourceName(
        const String& name
    ){
        resource_name_ = name;
    }
    
    ///
    /// リソース名取得
    const String& resourceName() const {
        return resource_name_;
    }
    
    ///
    /// リソースID取得
    UniqueID resourceID() const {
        return resource_id_;
    }
    
private:
    UniqueID resource_id_;          ///< リソースUD
    String resource_name_;          ///< リソース名
};


TRI_CORE_NS_END

#endif // TRI_RESOURCE_HPP_INCLUDED
