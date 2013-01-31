#include "DxLib.h"
#include "Pad.h"
#include "Player.h"

struct Player
{
    int area;
    int hougaku;
}; 

// ‰Šú‰»‚ğ‚·‚é
Player *Player_Initialize( )
{
	Player *self;
	self = (Player *)malloc(sizeof(Player));
	
	self->area = 0;
	self->hougaku = 0;
	return self;
}

void Player_set_area(Player *self, int area)
{
	self->area = area;
}

void Player_set_hougaku(Player *self, int hougaku)
{
	self->hougaku = hougaku;
}



// “®‚«‚ğŒvZ‚·‚é
void Player_Update( Player *self )
{
    
}

// •`‰æ‚·‚é
void Player_Draw( Player *self)
{
    
}

// I—¹ˆ—‚ğ‚·‚é
void Player_Finalize( Player *self )
{
    
}
