#include "DxLib.h"
#include "Keyboard.h"
#include "Room.h"

struct Room
{
    int model;
	VECTOR cam;
	double rotY;
}; 

// ‰Šú‰»‚ğ‚·‚é
Room *Room_Initialize()
{
	Room *self;
	self = (Room *)malloc(sizeof(Room));
    self->model = MV1LoadModel("meta/room.mqo") ;    //‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[
	MV1SetScale(self->model,VGet(10,10,10));
	self->cam = VGet(0.0f,500.0f,-500.0f);
	self->rotY = 0.0f;
	return self;
}

// “®‚«‚ğŒvZ‚·‚é
void Room_Update( Room *self )
{
	//

	if( 1==CheckHitKey(KEY_INPUT_LEFT) ) self->cam.x-=5;
        if( 1==CheckHitKey(KEY_INPUT_RIGHT) ) self->cam.x+=5;
        if( 1==CheckHitKey(KEY_INPUT_LSHIFT) || 1==CheckHitKey(KEY_INPUT_RSHIFT) ) {
            if( 1==CheckHitKey(KEY_INPUT_UP) ) self->cam.z+=5;
            if( 1==CheckHitKey(KEY_INPUT_DOWN) ) self->cam.z-=5;
        } else {
            if( 1==CheckHitKey(KEY_INPUT_UP) ) self->cam.y+=5;
            if( 1==CheckHitKey(KEY_INPUT_DOWN) ) self->cam.y-=5;
        }
        SetCameraPositionAndTarget_UpVecY(self->cam,VGet(0.0f,0.0f,0.0f));
        

		MV1SetPosition(self->model, VGet( 200.0f, 0.0f, 300.0f ) );
        MV1SetRotationXYZ( self->model, VGet( 0.0f, self->rotY, 0.0f ) );

		self->rotY += PHI / 180.0f;
}		

// •`‰æ‚·‚é
void Room_Draw( Room *self)
{
	MV1DrawModel( self->model);    
}

// I—¹ˆ—‚ğ‚·‚é
void Room_Finalize( Room *self )
{
    
}
