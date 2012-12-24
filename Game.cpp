#include "DxLib.h"
#include "Game.h"
#include "Script.h"
#include "Pad.h"

static const int NUM = 2;        //プレイヤーの数

struct Game
{
	Script *script;
	int hougaku;
	int area;
};

// 初期化をする
Game *Game_Initialize()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout); 
	freopen("CONIN$", "r", stdin);

	Game *self;
	self = (Game *)malloc(sizeof(Game));
	self->script = Script_Initialize( );
	self->hougaku = 0;
	self->area = 0;

	return self;
}


// 動きを計算する
void Game_Update(Game *self)
{
	if(Pad_Get( KEY_INPUT_RIGHT ) == -1)
	{
		if(self->hougaku == 3){self->hougaku = 0;}
		else{self->hougaku++;}
	}
	else if(Pad_Get( KEY_INPUT_LEFT ) == -1)
	{
		if(self->hougaku == 0){self->hougaku = 3;}
		else{self->hougaku--;}
	}

	if(Pad_Get( KEY_INPUT_RETURN ) == -1)
	{
		printf("\nmuki = %d\n",self->hougaku);
	}
	

	/*
	if(self->area == 0 && self->hougaku == 0 && 1)
	{

	}
	*/

	Script_Update( self->script );
}

// 描画する
void Game_Draw(Game *self)
{
	 Script_Draw( self->script );
	 
	 
     
}

// 終了処理をする
void Game_Finalize(Game *self )
{
	
}
