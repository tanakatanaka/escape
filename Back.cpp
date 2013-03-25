#include "DxLib.h"
#include "Pad.h"
#include "Back.h"

struct Back
{
	int sphere;
}; 

// ‰Šú‰»‚ğ‚·‚é
Back *Back_Initialize( )
{
	Back *self;
	self = new Back();
	
	self->sphere = MV1LoadModel("meta/back/sphere.mqo") ;    //model‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[

	return self;
}


// “®‚«‚ğŒvZ‚·‚é
void Back_Update( Back *self )
{
	MV1SetPosition(self->sphere, VGet( 200, 0, 300 ) );
}

// •`‰æ‚·‚é
void Back_Draw( Back *self)
{
	SetFogEnable(FALSE);
	MV1DrawModel(self->sphere);

}

// I—¹ˆ—‚ğ‚·‚é
void Back_Finalize( Back *self )
{
	
}
