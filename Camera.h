#ifndef DEF_Camera_H //��dinclude�h�~

#define DEF_Camera_H

struct Camera;

// ������������
Camera *Camera_Initialize( );

//game���猻�݂̈ʒu�����炤�֐�
void Camera_get_area(Camera *self, int area);
//game���獶�E��]�����炤�֐�
void Camera_get_muki(Camera *self, int muki);
/*game����J�������[�h(���s�E���_)�����炤�֐�
�������_���[�h�ɂȂ�ꍇ���p�����炤*/
void Camera_get_camera_mode(Camera *self, int camera_mode, int hougaku);
// �������v�Z����
void Camera_Update( Camera *Camera );

// �`�悷��
void Camera_Draw( Camera *Camera );

// �I������������
void Camera_Finalize( Camera *Camera );

#endif