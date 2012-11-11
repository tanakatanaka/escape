#include "DxLib.h"
#include "Keyboard.h"
#include "Player.h"

struct Player
{
    int Image;
    int y;
}; 

// ‰Šú‰»‚ð‚·‚é
Player *Player_Initialize( int y, int img )
{
	Player *self;
	self = (Player *)malloc(sizeof(Player));
    self->Image = img;    //‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[
    self->y     = y;        //yÀ•WŠi”[
	return self;
}

// “®‚«‚ðŒvŽZ‚·‚é
void Player_Update( Player *self )
{
    if( Keyboard_Get( KEY_INPUT_UP   ) > 0 )
	{//ã‚ª‰Ÿ‚³‚ê‚Ä‚¢‚½‚ç
        self->y--;
    }
    if( Keyboard_Get( KEY_INPUT_DOWN ) > 0 )
	{//‰º‚ª‰Ÿ‚³‚ê‚Ä‚¢‚½‚ç
        self->y++;
    }
}

// •`‰æ‚·‚é
void Player_Draw( Player *self){
    DrawGraph( 0, self->y, self->Image, TRUE );
}

// I—¹ˆ—‚ð‚·‚é
void Player_Finalize( Player *self )
{
    DeleteGraph( self->Image );
}
