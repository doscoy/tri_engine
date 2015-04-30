
#ifndef TRI_MATRIX_STACK_HPP_INCLUDED
#define TRI_MATRIX_STACK_HPP_INCLUDED


#include "tri_matrix.hpp"
#include <stack>


namespace t3 {


class MatrixStack
{

public:
    MatrixStack();
    ~MatrixStack();


public:
    void pushMatrix();
    void popMatrix();
    void multMatrixLocal(const Mtx44& mtx);
    const Mtx44* topMatrix() const;
    void clearStack();
    size_t getStackSize() const {
        return stack_.size();
    }
    
private:
    std::stack<Mtx44> stack_;
    Mtx44 top_;

};


}   // namespace t3


#endif // TRI_MATRIX_STACK_HPP_INCLUDED