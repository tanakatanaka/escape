#include "DxLib.h"
#include "Keyboard.h"
#include "Camera.h"

struct Camera
{
	VECTOR cam;
}; 

// ������������
Camera *Camera_Initialize()
{
	Camera *self;
	self = (Camera *)malloc(sizeof(Camera));
	return self;
}

// �������v�Z����
void Camera_Update( Camera *self )
{
    
}

// �`�悷��
void Camera_Draw( Camera *self){
   
}

// �I������������
void Camera_Finalize( Camera *self )
{

}
