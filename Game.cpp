#include "DxLib.h"
#include "Game.h"
#include "Script.h"

static const int NUM = 2;        //プレイヤーの数

struct Game
{
	Script *script;
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
	
	return self;
}


// 動きを計算する
void Game_Update(Game *self)
{
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
