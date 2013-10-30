
#ifndef TRI_MATRIX_STACK_HPP_INCLUDED
#define TRI_MATRIX_STACK_HPP_INCLUDED


#include "tri_matrix.hpp"
#include <stack>


namespace t3 {
namespace math {

class MatrixStack
{

public:
    MatrixStack();
    ~MatrixStack();


public:
    void pushMatrix();
    void popMatrix();
    void multMatrixLocal(const mtx4_t& mtx);
    const mtx4_t* getTopMatrix() const;
    
private:
    std::stack<mtx4_t> stack_;
    mtx4_t top_;

};

}   // namespace math
}   // namespace t3


#endif // TRI_MATRIX_STACK_HPP_INCLUDED