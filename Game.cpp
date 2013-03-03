#include "DxLib.h"
#include "Game.h"
#include "Console.h"
#include "Script.h"
#include "Pad.h"
#include "Opening.h"
#include "Player.h"
#include "Room.h"
#include "Ending.h"


struct Game
{
	Script *script;
	Camera *camera;
	Console *console;
	Player *player;
	Opening *opening;
	Room *room;
	Ending *ending;
	
	//game進行関係
	int game_state;
	
};

// 初期化をする
Game *Game_Initialize()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout); 
	freopen("CONOUT$", "w", stderr);
	freopen("CONIN$", "r", stdin);

	Game *self;
	self = new Game();
	self->console = Console_Initialize();
	self->camera = Camera_Initialize(self->console);
	self->room = Room_Initialize();
	self->player = Player_Initialize(self->camera, self->console, self->room);
	self->script = Script_Initialize(self->camera, self->console, self->player, self->room);
	self->opening = Opening_Initialize();
	self->ending = Ending_Initialize();
	//game進行関係
	self->game_state = 0;
	return self;
}

void game_play_Update(Game *self)
{
	Player_Update( self->player );
	Room_Update( self->room );
	Script_Update( self->script );
	Camera_Update(self->camera);
	Console_Update( self->console );
}

void game_play_Draw(Game *self)
{
	Player_Draw( self->player);
	Room_Draw(self->room);
	Script_Draw( self->script );
	Camera_Draw(self->camera);
	Console_Draw( self->console );
}

void game_play_Finalize(Game *self)
{
	Player_Finalize( self->player);
	Room_Finalize(self->room);
	Script_Finalize( self->script );
	Camera_Finalize(self->camera);
	Console_Finalize( self->console );
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
		game_play_Update(self);
		if(Player_get_time(self->player) < 0)
		{
			game_play_Finalize(self);
			self->game_state++;
		}
	}
	else if(self->game_state  == 2)
	{
		Ending_Update( self->ending );
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
		game_play_Draw(self);
	}
	else if(self->game_state  == 2)
	{
		Ending_Draw( self->ending );
	}

}

// 終了処理をする
void Game_Finalize(Game *self )
{
	free(self);
}
