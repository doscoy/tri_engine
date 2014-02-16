
#ifndef TRI_MATRIX_STACK_HPP_INCLUDED
#define TRI_MATRIX_STACK_HPP_INCLUDED


#include "tri_matrix.hpp"
#include <stack>


namespace t3 {
inline namespace math {

class MatrixStack
{

public:
    MatrixStack();
    ~MatrixStack();


public:
    void pushMatrix();
    void popMatrix();
    void multMatrixLocal(const Mtx4& mtx);
    const Mtx4* getTopMatrix() const;
    void clearStack();
    size_t getStackSize() const {
        return stack_.size();
    }
    
private:
    std::stack<Mtx4> stack_;
    Mtx4 top_;

};

}   // namespace math
}   // namespace t3


#endif // TRI_MATRIX_STACK_HPP_INCLUDED