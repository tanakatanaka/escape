#include "DxLib.h"
#include "Game.h"
#include "Console.h"
#include "Script.h"
#include "Opening.h"
#include "Game_play.h"
#include "Ending.h"
#include "Sound.h"

#define LOAD -1
#define OPEN 0
#define GAME_PLAY 1
#define END 2

struct Game
{
	Opening *opening;
	Game_play *game_play;
	Ending *ending;
	Sound *sound;


	//gameisŠÖŒW
	int game_state;
	
};

// ‰Šú‰»‚ð‚·‚é
Game *Game_Initialize()
{
	Game *self;
	self = new Game();
	self->sound = Sound_Initialize();
	//gameisŠÖŒW
	self->game_state = LOAD;
	return self;
}

// “®‚«‚ðŒvŽZ‚·‚é
bool Game_Update(Game *self)
{
	if(self->game_state  == LOAD)
	{
		self->opening = Opening_Initialize(self->sound);
		self->game_state++;
	}
	else if(self->game_state  == OPEN)
	{
		Opening_Update(self->opening);
		
		if(Opening_get_game_mode(self->opening)  == 1)
		{
			Opening_Finalize( self->opening );
			self->game_state  = GAME_PLAY;
			self->game_play = Game_play_Initialize(self->sound); 
		}
		else if(Opening_get_game_mode(self->opening)  == 0)
		{
			Opening_Finalize( self->opening );
			return false;
		}
	}
	else if(self->game_state  == GAME_PLAY)
	{
		Game_play_Update(self->game_play);
		Player *player = Game_play_get_result(self->game_play);

		if( player != NULL)
		{
			self->game_state++;
			self->ending = Ending_Initialize(player, self->sound);
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
		else if(Ending_get_next( self->ending ) ==  0)
		{
			Ending_Finalize( self->ending );
			return false;
		}
	}
	return true;
}

// •`‰æ‚·‚é
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

// I—¹ˆ—‚ð‚·‚é
void Game_Finalize(Game *self )
{
	Sound_Finalize( self->sound );
	delete self;
}
