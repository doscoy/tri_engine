
#ifndef TRI_RESOURCE_HPP_INCLUDED
#define TRI_RESOURCE_HPP_INCLUDED


#include "../util/tri_identifiable.hpp"
#include "../util/tri_namable.hpp"
#include "../util/tri_uncopyable.hpp"
#include "../io/tri_file.hpp"
#include "tri_develop_base.hpp"

namespace t3 {

class Resource
    : public Identifiable
    , public Namable
    , private Uncopyable
{
public:
    Resource(){}
    virtual ~Resource(){}
    
public:
    virtual const byte* getData() const = 0;

};

}   // namespace t3

#endif // TRI_RESOURCE_HPP_INCLUDED
