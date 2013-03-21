#include "DxLib.h"
#include "Pad.h"
#include "Player.h"
#include "Ending.h"

struct Ending
{
	Player *player;
	int next_game;
}; 

// ‰Šú‰»‚ğ‚·‚é
Ending *Ending_Initialize(Player *player)
{
	Ending *self;
	self = new Ending();
	self->player = player;
	self->next_game = 0;
	return self;
}

int Ending_get_next( Ending *self )
{
	return self->next_game;
}


// “®‚«‚ğŒvZ‚·‚é
void Ending_Update( Ending *self )
{
	if( Pad_Get( KEY_INPUT_RETURN ) == -1)
	{
		self->next_game = 1;
	}

}

// •`‰æ‚·‚é
void Ending_Draw( Ending *self)
{
	
}

// I—¹ˆ—‚ğ‚·‚é
void Ending_Finalize( Ending *self )
{
	
}
