#ifndef TRI_CAMERA_UPDATER_HPP_INCLUDED
#define TRI_CAMERA_UPDATER_HPP_INCLUDED

//  include
#include "../math/tri_math.hpp"
#include "tri_camera.hpp"
#include "base/tri_std.hpp"


namespace t3 {


///
/// �J��������
class CameraUpdater
{
public:
    ///
    /// �R���X�g���N�^
    CameraUpdater(){}


    ///
    /// �f�X�g���N�^
    virtual ~CameraUpdater(){}

public:
    ///
    /// �Ǘ�����J�����ݒ�
    void camera(
        SharedPtr<Camera> camera
    ) {
        camera_ = camera;
    }
    
protected:
    ///
    /// �Ǘ�����J�����擾
    CameraPtr camera() {
        return camera_;
    }
    
private:
    CameraPtr camera_;  ///< �Ǘ����Ă���J����
};


///
/// �ʒu�E�����_�ɂ�鐧��
///
class LookAtCameraUpdater
    : public CameraUpdater
{
public:
    ///
    /// �R���X�g���N�^
    LookAtCameraUpdater();

    ///
    /// �f�X�g���N�^
    virtual ~LookAtCameraUpdater();


public:
    ///
    /// ���W�ݒ�
    void position(const Vec3& v);

    ///
    /// ���W�ݒ�
    void position(float x, float y, float z);

    ///
    /// �����_�ݒ�
    void targetPosition(const Vec3& v);

    /// 
    /// �����_�ݒ�
    void targetPosition(float x, float y, float z);

    ///
    /// x���h���[
    void dollyX( 
        const float speed ///< ���x
    );

    ///
    /// y���h���[
    void dollyY( 
        const float speed ///< ���x
    );

    ///
    /// z���h���[
    void dollyZ( 
        const float speed ///< ���x
    );

    ///
    /// �C�ӕ����h���[
    void dolly(
        const Vec3& dir,    ///< ����
        const float speed   ///< ���x
    );

    ///
    /// �c��U��
    void panV( const float speed );

    ///
    /// ����U��
    void panH( const float speed );

    ///
    /// �C�ӎ���U��
    void pan(
        const Vec3& axis,   ///< ��
        const float speed   ///< ���x
    );
    

private:


};


}   // namespace t3

#endif // TRI_CAMERA_UPDATER_HPP_INCLUDED
