#ifndef DEF_Camera_H //��dinclude�h�~

#define DEF_Camera_H

struct Camera;

// ������������
Camera *Camera_Initialize( );

//game���猻�݂̈ʒu�����炤�֐�
void Camera_get_area(Camera *self, int area);
//game���獶�E��]�����炤�֐�
void Camera_get_rl(Camera *self, int rl);

// �������v�Z����
void Camera_Update( Camera *Camera );

// �`�悷��
void Camera_Draw( Camera *Camera );

// �I������������
void Camera_Finalize( Camera *Camera );

#endif