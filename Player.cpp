#include "DxLib.h"
#include "Keyboard.h"
#include "Player.h"

struct Player
{
    int Image;
    int y;
} 

// ‰Šú‰»‚ğ‚·‚é
Player Player_Initialize( int y, int img )
{
	Player *self;
	self = (Player *)malloc(sizeof(Player));
    Player->Image = img;    //‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[
    Player->y     = y;        //yÀ•WŠi”[
	return *self;
}

// “®‚«‚ğŒvZ‚·‚é
void Player_Update( Player *Player )
{
    if( Keyboard_Get( KEY_INPUT_UP   ) > 0 )
	{//ã‚ª‰Ÿ‚³‚ê‚Ä‚¢‚½‚ç
        Player->y--;
    }
    if( Keyboard_Get( KEY_INPUT_DOWN ) > 0 )
	{//‰º‚ª‰Ÿ‚³‚ê‚Ä‚¢‚½‚ç
        Player->y++;
    }
}

// •`‰æ‚·‚é
void Player_Draw( Player Player ){
    DrawGraph( 0, Player.y, Player.Image, TRUE );
}

// I—¹ˆ—‚ğ‚·‚é
void Player_Finalize( Player Player )
{
    DeleteGraph( Player.Image );
}
