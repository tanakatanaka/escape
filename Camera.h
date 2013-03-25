#ifndef DEF_Camera_H //��dinclude�h�~

#define DEF_Camera_H

struct Camera;

#include "console.h"

// ������������
Camera *Camera_Initialize( Console *console );

//game���猻�݂̈ʒu�����炤�֐�
void Camera_set_area(Camera *self, int area);
//���E��]��Ԃ��֐�(player_camera�ɂ���ĕԂ�l���ω�)
int Camera_get_hougaku(Camera *self);
//�J�����̎��_���[�h�̗L����Ԃ�
int Camera_is_look_at(Camera *self);

// �������v�Z����
void Camera_Update( Camera *Camera );

// DX�̃J��������ݒ肷��
void Camera_Draw( Camera *Camera );

// �w�i�p�Ɉʒu�w�蔲����DX�̃J������ݒ肷��
void Camera_Draw_back(Camera *self);

// �I������������
void Camera_Finalize( Camera *Camera );

#endif