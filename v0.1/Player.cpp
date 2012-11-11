#include "DxLib.h"
#include "Keyboard.h"
#include "Player.h"

struct Player
{
    int Image;
    int y;
}; 

// 初期化をする
Player *Player_Initialize( int y, int img )
{
	Player *self;
	self = (Player *)malloc(sizeof(Player));
    self->Image = img;    //画像ハンドルの格納
    self->y     = y;        //y座標格納
	return self;
}

// 動きを計算する
void Player_Update( Player *self )
{
    if( Keyboard_Get( KEY_INPUT_UP   ) > 0 )
	{//上が押されていたら
        self->y--;
    }
    if( Keyboard_Get( KEY_INPUT_DOWN ) > 0 )
	{//下が押されていたら
        self->y++;
    }
}

// 描画する
void Player_Draw( Player *self){
    DrawGraph( 0, self->y, self->Image, TRUE );
}

// 終了処理をする
void Player_Finalize( Player *self )
{
    DeleteGraph( self->Image );
}
