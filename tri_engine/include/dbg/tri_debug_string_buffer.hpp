
#ifndef TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED
#define TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED

#include "base/tri_std.hpp"
#include "util/tri_uncopyable.hpp"


namespace t3 {


///
/// �f�o�b�O�����̃R���e�i�̃T�C�Y
constexpr int DEBUG_STRING_ITEM_STR_SIZE = 95;

///
/// �f�o�b�O�p����
struct DebugStringItem {
    uint32_t color_;
    int16_t x_;
    int16_t y_;
    char str_[DEBUG_STRING_ITEM_STR_SIZE];
    char size_;
};

///
/// �f�o�b�O�����o�b�t�@
class DebugStringBuffer
    : private Uncopyable
{
public:
    ///
    /// �R���X�g���N�^
    DebugStringBuffer();

    ///
    /// �f�X�g���N�^
    ~DebugStringBuffer();
    
    
public:
    ///
    /// �f�o�b�O������ǉ�
    void addString(
        const float x,          ///< �ʒu��
        const float y,          ///< �ʒu��
        const uint32_t color,   ///< �\���F
        const int size,         ///< �t�H���g�T�C�Y
        const char* const str   ///< ������
    );
    
    ///
    /// �o�b�t�@�N���A
    void clearBuffer();

    ///
    /// �o�b�t�@��`��
    void drawStrings();
    
private:
    ///
    /// ������̃R���e�i
    Array<DebugStringItem, 300> buffer_;

    ///
    /// �ǉ��ς݃T�C�Y
    int size_;
};





}   // namespace t3




#endif // TRI_DEBUG_STRING_BUFFER_HPP_INCLUDED