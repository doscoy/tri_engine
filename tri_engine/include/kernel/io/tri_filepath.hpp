

#ifndef TRI_FILEPATH_HPP_INCLUDED
#define TRI_FILEPATH_HPP_INCLUDED

//  include
#include "base/tri_std.hpp"


namespace t3 {

///
/// �t�@�C���p�X�N���X
class FilePath {
public:
    ///
    /// �R���X�g���N�^
    FilePath(
       const String& filepath
    );
    
    ///
    /// �f�X�g���N�^
    ~FilePath();

public:
    ///
    /// �t���p�X�擾
    String getFullPath() const;
    
    ///
    /// �g���q�擾
    String ext() const;
    
    ///
    /// �p�X�擾
    const String& path() const;
    
    ///
    /// �g���q�����̃t�@�C�������擾
    String getFileNameNotExt() const;
    
public:
    ///
    /// ���ʂ̃x�[�X�f�B���N�g����ݒ�
    static void setBaseDirectory(
        String const base
    );

private:
    String filepath_;               ///< �t�@�C���p�X
    static String base_filepath_;   ///< �x�[�X�f�B���N�g��
};


}   // namespace t3



#endif // TRI_FILEPATH_HPP_INCLUDED
