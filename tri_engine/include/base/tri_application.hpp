#ifndef TRI_APPLICATION_HPP_INCLUDED
#define TRI_APPLICATION_HPP_INCLUDED

//  �C���N���[�h
#include "util/tri_uncopyable.hpp"
#include "base/tri_std.hpp"
#include "tri_types.hpp"
#include "util/tri_stopwatch.hpp"


//  �O���錾
class ApplicationDebugMenu;



namespace t3 {


//  �O���錾
class SceneGenerator;

///
/// �A�v���P�[�V�����N���X.
/// �S�ẴA�v���P�[�V�����̊�_
class Application 
    : Uncopyable 
{
public:
    ///
    /// �R���X�g���N�^
    Application();

    ///
    /// �f�X�g���N�^
    virtual ~Application();


private:
    ///
    /// �Q�[�����̏�����
    virtual void initializeGame() = 0;

    ///
    /// �Q�[�����̌�Еt��
    virtual void terminateGame() = 0;

public:
    ///
    /// ������
    void initializeApplication();

    ///
    /// �X�V
    void updateApplication();

    ///
    /// �`��
    void renderApplication();

    ///
    /// ��Еt��
    void terminateApplication();


    ///
    /// �A�v���P�[�V���������s��������
    bool isActive() const;

    ///
    /// �A�v���P�[�V�����̃��[�g�V�[����ݒ�
    void rootScene(
        SceneGenerator* root    ///< root
    ) {
        root_scene_generator_ = root;
    }
    
private:
    ///
    /// �`��O����
    void beginRender();

    ///
    /// �`��㏈��
    void endRender();


    ///
    /// �f�o�b�O���j���[�̃I�[�v�����N�G�X�g���������Ă��邩����
    bool isDebugMenuOpenRequest();

    ///
    /// �T�X�y���h��������
    bool isSuspend() const;

    ///
    /// ���[�N�o�[�̏�����
    void initializeWorkBar();

    ///
    /// �f�o�b�O�p�`��
    void debugPrinting();
public:
    ///
    /// ���[�g�V�[���֑J��
    void gotoRootScene();
    
    
private:
#if DEBUG
    ScopedPtr<ApplicationDebugMenu> system_menu_;
#endif
    SceneGenerator* root_scene_generator_;  ///< ���[�g�V�[���̃W�F�l���[�^
    uint32_t last_scene_change_frame_;  ///< �Ō�ɃV�[���`�F���W�����t���[��
    uint32_t memory_leak_check_filter_; ///< ���������[�N�`�F�b�N�t�B���^
    Stopwatch fps_timer_;   ///< fps�v���p�^�C�}�[
    Array<float, 260> fps_stack_;   ///< fps�ۑ��p�R���e�i
    float fps_; ///< fps
};




///
/// �G���W���̏�����
void initializeTriEngine(
    const int width,
    const int height,
    const char* const title
    );


///
/// �G���W���̌�Еt��
void terminateTriEngine();


///
/// �N������A�v����ݒ�.
void setApplication(Application& app);


///
/// ������.
void initializeApplication();


///
/// ��Еt��.
void terminateApplication();

///
/// �X�V.
void updateApplication();

///
/// �`��.
void renderApplication();


}   // namespace t3

#endif // TRI_APPLICATION_HPP_INCLUDED
