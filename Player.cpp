#include "DxLib.h"
#include "Keyboard.h"
#include "Player.h"

typedef struct
{
    int Image;
    int y;
} Player_t;

// 初期化をする
Player_t Player_Initialize( int y, int img )
{
	Player_t *self;
    Player->Image = img;    //画像ハンドルの格納
    Player->y     = y;        //y座標格納
	return self
}

// 動きを計算する
void Player_Update( Player_t *Player )
{
    if( Keyboard_Get( KEY_INPUT_UP   ) > 0 )
	{//上が押されていたら
        Player->y--;
    }
    if( Keyboard_Get( KEY_INPUT_DOWN ) > 0 )
	{//下が押されていたら
        Player->y++;
    }
}

// 描画する
void Player_Draw( Player_t Player ){
    DrawGraph( 0, Player.y, Player.Image, TRUE );
}

// 終了処理をする
void Player_Finalize( Player_t Player ){
    DeleteGraph( Player.Image );
}
