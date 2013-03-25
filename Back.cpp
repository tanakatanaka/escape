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

	return self;
}


// �������v�Z����
void Back_Update( Back *self )
{
	VECTOR pt = Camera_get_angle(self->camera);

	SetCameraPositionAndTarget_UpVecY(VGet( 0.0f, 0.0f, 0.0f ),pt);
	MV1SetPosition(self->sphere, VGet( 200, 0, 300 ) );
}

// �`�悷��
void Back_Draw( Back *self)
{
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
