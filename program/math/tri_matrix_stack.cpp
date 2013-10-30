
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
    const Mtx4& mtx
) {
    top_ = top_ * mtx;
}


const Mtx4* MatrixStack::getTopMatrix() const
{
    return &top_;
}


  
}   // namespace math
}   // namespace t3

