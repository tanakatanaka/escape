#include "DxLib.h"
#include "Game.h"
#include "Console.h"
#include "Script.h"
#include "Opening.h"
#include "Game_play.h"
#include "Ending.h"

#define LOAD -1
#define OPEN 0
#define GAME_PLAY 1
#define END 2

struct Game
{
	Opening *opening;
	Game_play *game_play;
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
	//game進行関係
	self->game_state = LOAD;
	return self;
}

// 動きを計算する
void Game_Update(Game *self)
{
	if(self->game_state  == LOAD)
	{
		self->opening = Opening_Initialize();
		self->game_state++;
	}
	else if(self->game_state  == OPEN)
	{
		Opening_Update(self->opening);
		
		if(Opening_get_game_mode(self->opening)  == 1)
		{
			Opening_Finalize( self->opening );
			self->game_state  = GAME_PLAY;
			self->game_play = Game_play_Initialize(); 
		}
	}
	else if(self->game_state  == GAME_PLAY)
	{
		Game_play_Update(self->game_play);
		Player *player = Game_play_get_result(self->game_play);

		if( player != NULL)
		{
			self->game_state++;
			self->ending = Ending_Initialize(player);
		}
	}
	else if(self->game_state  == END)
	{
		Ending_Update( self->ending );
		if(Ending_get_next( self->ending ) ==  1)
		{
			Game_play_Finalize(self->game_play );
			Ending_Finalize( self->ending );
			self->game_state = LOAD;
		}

	}
}

// 描画する
void Game_Draw(Game *self)
{
	if(self->game_state  == OPEN)
	{
		Opening_Draw(self->opening);
	}
	else if(self->game_state  == GAME_PLAY)	
	{
		Game_play_Draw(self->game_play);
	}
	else if(self->game_state  == END)
	{
		Ending_Draw( self->ending );
	}

}

// 終了処理をする
void Game_Finalize(Game *self )
{
	free(self);
}
