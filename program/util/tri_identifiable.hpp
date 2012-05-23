
#ifndef TRI_IDENTIFIABLE_HPP_INCLUDED
#define TRI_IDENTIFIABLE_HPP_INCLUDED

#include "tri_unique_id.hpp"
#include "tri_uncopyable.hpp"


namespace t3 {

class Identifiable
    : private Uncopyable
{
public:
    // *********************************************
    //  コンストラクタ
    Identifiable(){
        id_ = uniqueID();
    }

    // *********************************************
    //  デストラクタ
    ~Identifiable(){}

public:
    // *********************************************
    //  IDを取得
    uid_t getID() const {
        return id_;
    }

private:
    uid_t id_;
};


}   // namespace t3

#endif // TRI_IDENTIFIABLE_HPP_INCLUDED
