#include "DxLib.h"
#include "Room.h"


struct Room
{
    int room;
	int test;
	double rotY;
}; 

// ‰Šú‰»‚ğ‚·‚é
Room *Room_Initialize()
{
	Room *self;
	self = (Room *)malloc(sizeof(Room));
    self->room = MV1LoadModel("meta/room.mqo") ;    //‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[
	self->test = MV1LoadModel("meta/test.mqo") ; 
	
	self->rotY = 0.0f;
	return self;
}

// “®‚«‚ğŒvZ‚·‚é
void Room_Update( Room *self )
{
	//–¶•`‰æon:‚É‚Â‚¢‚Äcolor‚ÅF
	SetFogEnable( TRUE );
	SetFogColor( 0, 0, 0 );


	MV1SetPosition(self->room, VGet( 200.0f, 0.0f, 300.0f ) );
    MV1SetRotationXYZ( self->room, VGet( 0.0f, self->rotY, 0.0f ) );

	MV1SetPosition(self->test, VGet( 0, 0, 0 ) );
    MV1SetRotationXYZ( self->test, VGet( 0, self->rotY, 0 ) );

	if(CheckHitKey(KEY_INPUT_A)){self->rotY -= (PHI / 180.0f);}
	else if(CheckHitKey(KEY_INPUT_D)){self->rotY += (PHI / 180.0f);}
}		

// •`‰æ‚·‚é
void Room_Draw( Room *self)
{
	MV1DrawModel( self->room);    
	MV1DrawModel( self->test); 
}

// I—¹ˆ—‚ğ‚·‚é
void Room_Finalize( Room *self )
{
    
}
