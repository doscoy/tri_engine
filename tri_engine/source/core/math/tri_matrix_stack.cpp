
#include "core/math/tri_matrix_stack.hpp"

TRI_CORE_NS_BEGIN



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
//    top_ = mtx * top_;
    top_ = top_ * mtx;
}


const Mtx44* MatrixStack::topMatrix() const
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




TRI_CORE_NS_END
