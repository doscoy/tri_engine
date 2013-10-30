
#include "tri_matrix_stack.hpp"

namespace t3 {
inline namespace math {

MatrixStack::MatrixStack()
    : stack_()
    , top_()
{

}

MatrixStack::~MatrixStack()
{

}

void MatrixStack::pushMatrix()
{
    stack_.push(top_);
}


void MatrixStack::popMatrix()
{
    stack_.pop();
}

void MatrixStack::multMatrixLocal(
    const mtx4_t& mtx
) {
    top_ = top_ * mtx;
}


const mtx4_t* MatrixStack::getTopMatrix() const
{
    return &top_;
}


  
}   // namespace math
}   // namespace t3

