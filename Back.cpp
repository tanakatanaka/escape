#include "DxLib.h"
#include "Pad.h"
#include "Back.h"
#include "Camera.h"

struct Back
{
	int sphere;
	Camera *camera;
}; 

// ������������
Back *Back_Initialize( Camera *camera)
{
	Back *self;
	self = new Back();
	self->camera = camera;
	self->sphere = MV1LoadModel("meta/back/sphere.mqo") ;    //model�摜�n���h���̊i�[
	MV1SetUseZBuffer(self->sphere, FALSE);
	MV1SetPosition(self->sphere, VGet( 0, 0, 0 ) );

	return self;
}


// �������v�Z����
void Back_Update( Back *self )
{
}

// �`�悷��
void Back_Draw( Back *self)
{
	Camera_Draw_back(self->camera);

	SetFogEnable(FALSE);
	MV1DrawModel(self->sphere);
	
	//���`��on:�ɂ���color�ŐF�Est�`�n�I
    SetFogEnable(TRUE);
    SetFogColor(0, 0, 0);
    SetFogStartEnd(500,  1500) ;
}

// �I������������
void Back_Finalize( Back *self )
{
	SetFogEnable(FALSE);
}
