#include "DxLib.h"
#include "Keyboard.h"
#include "Room.h"

struct Room
{
    int model;
	float rotY;
}; 

// ‰Šú‰»‚ğ‚·‚é
Room *Room_Initialize()
{
	Room *self;
	self = (Room *)malloc(sizeof(Room));
    self->model = MV1LoadModel("meta/room.mqo") ;    //‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[
	
	self->rotY = 0.0f;
	return self;
}

// “®‚«‚ğŒvZ‚·‚é
void Room_Update( Room *self )
{
	//

	
        

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
