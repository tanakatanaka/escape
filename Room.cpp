#include "DxLib.h"
#include "Keyboard.h"
#include "Room.h"

struct Room
{
    int model;
}; 

// ‰Šú‰»‚ğ‚·‚é
Room *Room_Initialize()
{
	Room *self;
	self = (Room *)malloc(sizeof(Room));
    self->model = MV1LoadModel("room.mqo") ;    //‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[
	MV1SetPosition(self->model, VGet( 320.0f, -300.0f, 600.0f ) ) ;
	return self;
}

// “®‚«‚ğŒvZ‚·‚é
void Room_Update( Room *self )
{
    if( Keyboard_Get( KEY_INPUT_UP   ) > 0 )
	{//ã‚ª‰Ÿ‚³‚ê‚Ä‚¢‚½‚ç
       
    }
    if( Keyboard_Get( KEY_INPUT_DOWN ) > 0 )
	{//‰º‚ª‰Ÿ‚³‚ê‚Ä‚¢‚½‚ç
        
    }
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
