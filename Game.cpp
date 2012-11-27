#include "DxLib.h"
#include "Game.h"
#include "Console.h"
#include "Script.h"

static const int NUM = 2;        //プレイヤーの数

struct Game
{
	Console *console;
	Script *script;
};

// 初期化をする
Game *Game_Initialize()
{
	Game *self;
	self = (Game *)malloc(sizeof(Game));
	self->console = Console_Initialize( );
	self->script = Script_Initialize( );
	AllocConsole();
	freopen("CONOUT$", "w", stdout); 
	freopen("CONIN$", "r", stdin);


	return self;
}


// 動きを計算する
void Game_Update(Game *self)
{
	Console_Update( self->console );
	Script_Update( self->script );
}

// 描画する
void Game_Draw(Game *self)
{
	 
	 Console_Draw( self->console );
	 Script_Draw( self->script );
     
}

// 終了処理をする
void Game_Finalize(Game *self )
{
	
}
