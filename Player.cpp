#include "DxLib.h"
#include "Pad.h"
#include "Player.h"

struct Player
{
    int area;
    int hougaku;
}; 

// 初期化をする
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



// 動きを計算する
void Player_Update( Player *self )
{
    
}

// 描画する
void Player_Draw( Player *self)
{
    
}

// 終了処理をする
void Player_Finalize( Player *self )
{
    
}
