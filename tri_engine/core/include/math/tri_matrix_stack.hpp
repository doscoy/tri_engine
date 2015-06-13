/**
    @file tri_matrix_stack.hpp
    行列スタック.
*/

#ifndef TRI_MATRIX_STACK_HPP_INCLUDED
#define TRI_MATRIX_STACK_HPP_INCLUDED

// include
#include "core_config.hpp"
#include "tri_matrix.hpp"
#include <stack>


TRI_CORE_NS_BEGIN


///
/// 行列スタック
class MatrixStack
{

public:
    ///
    /// コンストラクタ
    MatrixStack();
    
    ///
    /// デストラクタ
    ~MatrixStack();


public:
    ///
    /// プッシュ
    void pushMatrix();
    
    ///
    /// ポップ
    void popMatrix();
    
    ///
    /// 行列を合成
    void multMatrixLocal(const Mtx44& mtx);
    
    ///
    /// 最上位行列取得
    const Mtx44* topMatrix() const;
    
    ///
    /// スタックをクリア
    void clearStack();
    
    ///
    /// スタックサイズ取得
    size_t getStackSize() const {
        return stack_.size();
    }
    
private:
    ///
    /// 行列スタック
    std::stack<Mtx44> stack_;
    
    ///
    /// 最上位行列
    Mtx44 top_;

};


TRI_CORE_NS_END


#endif // TRI_MATRIX_STACK_HPP_INCLUDED