#ifndef DEF_Camera_H //��dinclude�h�~

#define DEF_Camera_H

struct Camera;

// ������������
Camera *Camera_Initialize( );

//game���猻�݂̈ʒu�����炤�֐�
void Camera_get_area(Camera *self, int area);
//game���獶�E��]�����炤�֐�
void Camera_get_muki(Camera *self, int muki);
//camera�̕��p�����炤�֐�;
int Camera_look_to(Camera *self);
/*game����J�������[�h(���s�E���_)�����炤�֐�
�������_���[�h�ɂȂ�ꍇ���p�����炤*/
int Camera_get_camera_mode(Camera *self, int camera_mode);
//���_����̒l�����..type0:x,type1:y
void Camera_get_pt(Camera *self, int type, float point);
// �������v�Z����
void Camera_Update( Camera *Camera );

// �`�悷��
void Camera_Draw( Camera *Camera );

// �I������������
void Camera_Finalize( Camera *Camera );

#endif