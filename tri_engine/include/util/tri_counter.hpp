#ifndef TRI_COUNTER_HPP_INCLUDED
#define TRI_COUNTER_HPP_INCLUDED

namespace t3 {

///
/// �J�E���^�[�N���X
class Counter {
public:
    ///
    /// �R���X�g���N�^
    Counter()
        : num_( 0 )
    {}
    
    
    ///
    /// ���ݒn
    int now() const {
        return num_;
    }
    
    ///
    /// �J�E���g�A�b�v
    void countup() {
        num_ += 1;
    }
    
    ///
    /// �J�E���g�_�E��
    void countdown() {
        num_ -= 1;
    }
    
private:
    int num_;   ///< �J�E���g�l
};


extern Counter frame_counter_;

}   // namespace t3



#endif // TRI_COUNTER_HPP_INCLUDED