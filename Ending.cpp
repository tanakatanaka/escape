#include "DxLib.h"
#include "Pad.h"
#include "Player.h"
#include "Ending.h"

struct Ending
{
	Player *player;
	int next_game;
}; 

// 初期化をする
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


// 動きを計算する
void Ending_Update( Ending *self )
{
	if( Pad_Get( KEY_INPUT_RETURN ) == -1)
	{
		self->next_game = 1;
	}

}

// 描画する
void Ending_Draw( Ending *self)
{
	
}

// 終了処理をする
void Ending_Finalize( Ending *self )
{
	
}
