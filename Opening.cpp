#include "DxLib.h"
#include "Pad.h"
#include "Opening.h"

struct Opening
{
     int room;
	 float plus;
	 int state;
	 int game_state;
	 int on_and_off;
}; 

// ‰Šú‰»‚ð‚·‚é
Opening *Opening_Initialize( )
{
	Opening *self;
	self = (Opening *)malloc(sizeof(Opening));
	self->room = MV1LoadModel("meta/room.mqo") ;    //model‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[
	self->plus = 0;
	self->state = 0;
	self->game_state = 0;
	self->on_and_off = 0;

	return self;
}

int Opening_get_game_state(Opening *self)
{
	return self->game_state;
}

void moji_enter(Opening *self)
{ 
	SetFontSize( 30 ) ;

	if(self->on_and_off % 100 < 80)
	{ 
		DrawFormatString( 0, 0, GetColor( 255, 20, 255 ), "%s", "Pless Enter key"); 
	}
}

void moji_game(Opening *self)
{ 
	SetFontSize( 30 ) ;
	DrawFormatString( 0, 0, GetColor( 20, 20, 255 ), "%s", "Game Start"); 
}

// “®‚«‚ðŒvŽZ‚·‚é
void Opening_Update( Opening *self )
{
	if(self->state == 0)
	{
		self->plus += PHI / 180.0f;
	}
	else if(self->state == 2)
	{
		self->game_state = 1;
	}
	
	if(Pad_Get(KEY_INPUT_RETURN) == 1)
	{
		self->state++;
	}
	
	self->on_and_off++;
}

// •`‰æ‚·‚é
void Opening_Draw( Opening *self)
{
	SetCameraPositionAndTarget_UpVecY(VGet( 1000, 1600, 0 ), VGet( 0, 0, 0 ) );
	//ƒ‚ƒfƒ‹ŠÖŒW
	MV1SetRotationXYZ( self->room, VGet( 0.0f, self->plus / 2, 0.0f ) );
	MV1DrawModel(self->room);

	if(self->state == 0){ moji_enter(self);}
	else if(self->state == 1){ moji_game(self);}
}

// I—¹ˆ—‚ð‚·‚é
void Opening_Finalize( Opening *self )
{
	MV1DeleteModel(self->room);
    free(self);
}
