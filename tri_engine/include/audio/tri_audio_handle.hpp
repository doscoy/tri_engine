#ifndef TRI_AUDIO_HANDLE_HPP_INCLUDED
#define TRI_AUDIO_HANDLE_HPP_INCLUDED

//  include
#include "cross_sdk.hpp"

namespace t3 {

//  �O���錾
class AudioResource;

class AudioHandle {
    friend class AudioResource;
private:
    ///
    /// �R���X�g���N�^.
    /// �I�[�f�B�I���\�[�X���炵�������ł��Ȃ����邽��private
    explicit AudioHandle(
        cross::AudioSystem::BufferID buffer_id
    );

public:
    ///
    /// �f�X�g���N�^
    ~AudioHandle();

public:
    ///
    /// BGM�Ƃ��čĐ�
    void playBGM();

    ///
    /// BGM�Ƃ��Ē�~
    void stopBGM();
    
    ///
    /// SE�Ƃ��čĐ�
    void playSE();

    ///
    /// SE�Ƃ��Ē�~
    void stopSE();

    ///
    /// �s�b�`�ݒ�
    void pitch(float speed);

    ///
    /// �{�����[���ݒ�
    void volume(float vol);

    ///
    /// BGM������
    bool isBGM() const {
        return bgm_;
    }

private:
    
    ///
    /// �Đ�����.
    void play(bool loop = false);

    ///
    /// ��~����.
    void stop();
    
private:
    
    cross::AudioSystem::SourceID sid_;  ///< �\�[�XID
    bool bgm_;  ///< BGM����p�t���O
};



}   // namespace t3

#endif // TRI_AUDIO_HANDLE_HPP_INCLUDED
