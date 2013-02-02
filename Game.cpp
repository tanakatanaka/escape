#include "DxLib.h"
#include "Game.h"
#include "Console.h"
#include "Script.h"
#include "Pad.h"
#include "Opening.h"
#include "Player.h"


struct Game
{
	Script *script;
	Camera *camera;
	Console *console;
	Player *player;
	Opening *opening;
	
	//game進行関係
	int game_state;
	
};

// 初期化をする
Game *Game_Initialize()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout); 
	freopen("CONIN$", "r", stdin);

	Game *self;
	self = new Game();
	self->console = Console_Initialize();
	self->camera = Camera_Initialize(self->console);
	self->player = Player_Initialize(self->camera, self->console);
	self->script = Script_Initialize(self->camera, self->console, self->player);
	self->opening = Opening_Initialize();
	//game進行関係
	self->game_state = 0;
	return self;
}

// 動きを計算する
void Game_Update(Game *self)
{
	if(self->game_state  == 0)
	{
		Opening_Update(self->opening);
		self->game_state = Opening_get_game_state(self->opening);
		if(self->game_state  == 1){ Opening_Finalize( self->opening ); }
	}
	else if(self->game_state  == 1)
	{
		Player_Update( self->player );
		Script_Update( self->script );
	}
}

// 描画する
void Game_Draw(Game *self)
{
	if(self->game_state  == 0)
	{
		Opening_Draw(self->opening);
	}
	else if(self->game_state  == 1)	
	{
		Player_Draw( self->player);
		Script_Draw( self->script );
	}
}

// 終了処理をする
void Game_Finalize(Game *self )
{
	free(self);
}
