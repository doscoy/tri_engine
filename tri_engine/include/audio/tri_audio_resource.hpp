#ifndef TRI_AUDIO_RESOURCE_HPP_INCLUDED
#define TRI_AUDIO_RESOURCE_HPP_INCLUDED

//  include
#include "base/tri_resource.hpp"
#include "base/tri_resource_manager.hpp"
#include "tri_audio_handle.hpp"


namespace t3 {

//  �O���錾
class Wav;

///
/// �I�[�f�B�I���\�[�X
class AudioResource final
    : Resource
{
private:
    /// 
    /// �R���X�g���N�^.
    /// create�֐��o�R�ł��������ł��Ȃ�
    AudioResource();

public:
    ///
    /// �f�X�g���N�^
    ~AudioResource();

    ///
    /// �T�E���h����
    SharedPtr<AudioHandle>  createSound();

public:
    ///
    /// ���\�[�X�̐����֐�.
    static SharedPtr<AudioResource> create(FilePath& filepath);



private:
    ///
    /// �o�b�t�@�\�z
    void setupBuffer(
        const Wav& wav  ///< wav����\�z
    );

private:
    cross::AudioSystem::BufferID id_;   ///< �o�b�t�@ID
};


///
/// �I�[�f�B�I���\�[�X�}�l�[�W��
using AudioManager = ResourceManager<AudioResource>;



} // namespace t3

#endif // TRI_AUDIO_RESOURCE_HPP_INCLUDED
