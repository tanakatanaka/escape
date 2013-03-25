#include "DxLib.h"
#include "Pad.h"
#include "Back.h"

struct Back
{
	int sphere;
}; 

// ������������
Back *Back_Initialize( )
{
	Back *self;
	self = new Back();
	
	self->sphere = MV1LoadModel("meta/back/sphere.mqo") ;    //model�摜�n���h���̊i�[

	return self;
}


// �������v�Z����
void Back_Update( Back *self )
{
	MV1SetPosition(self->sphere, VGet( 200, 0, 300 ) );
}

// �`�悷��
void Back_Draw( Back *self)
{
	SetFogEnable(FALSE);
	MV1DrawModel(self->sphere);

}

// �I������������
void Back_Finalize( Back *self )
{
	
}
