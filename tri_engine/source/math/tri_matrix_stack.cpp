
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
    top_ = stack_.top();
    stack_.pop();
}

void MatrixStack::multMatrixLocal(
    const Mtx44& mtx
) {
    top_ = mtx * top_;
//    top_ = top_ * mtx;
}


const Mtx44* MatrixStack::getTopMatrix() const
{
    return &top_;
}

void MatrixStack::clearStack()
{
    while (!stack_.empty()) {
        stack_.pop();
    }
    top_.identity();
}





  
}   // namespace math
}   // namespace t3

