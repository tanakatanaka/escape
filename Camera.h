#ifndef DEF_Camera_H //��dinclude�h�~

#define DEF_Camera_H

struct Camera;

// ������������
Camera *Camera_Initialize( );

// �������v�Z����
void Camera_Update( Camera *Camera );

// �`�悷��
void Camera_Draw( Camera *Camera );

// �I������������
void Camera_Finalize( Camera *Camera );

#endif