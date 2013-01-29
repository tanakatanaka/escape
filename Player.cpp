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
	return self;
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
