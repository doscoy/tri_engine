
#ifndef TRI_PNG_HPP_INCLUDED
#define TRI_PNG_HPP_INCLUDED

//  include
#include "../base/tri_types.hpp"
#include "kernel/io/tri_file.hpp"




namespace t3 {

///
/// png�C���[�W
struct PngImage {
    ///
    /// �R���X�g���N�^
    explicit PngImage(String path);

    ///
    /// �R���X�g���N�^
    explicit PngImage(const File& file);

    ///
    /// �f�X�g���N�^
    ~PngImage();

    uint32_t width_;        ///< ��
    uint32_t height_;       ///< ����
    uint8_t* data_;         ///< �f�[�^
    int bit_depth_;         ///< �r�b�g�[�x
    int color_type_;        ///< �J���[�^�C�v
    int interlace_type_;    ///< �C���^�[���[�X����
    int size_;              ///< �T�C�Y
};


}   // namespace t3

#endif // TRI_PNG_HPP_INCLUDED
