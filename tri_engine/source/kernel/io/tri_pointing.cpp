
#include "tri_pointing.hpp"


namespace t3{

Pointing::Pointing()
    : hold_(false)
    , trigger_(false)
    , release_(false)
{

}



Pointing::~Pointing()
{

}

void Pointing::updatePointing(
    const bool hit,
    const Point2& position
){

    trigger_ = hit & ( hit ^ hold_);
    release_ = hold_ & ( hit ^ hold_);
    hold_ = hit;
    
    
    position_ = position;
}

   
}   // namespace t3


