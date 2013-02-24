#include "DxLib.h"
#include "Game.h"
#include "Console.h"
#include "Script.h"
#include "Pad.h"
#include "Opening.h"
#include "Player.h"
#include "Room.h"


struct Game
{
	Script *script;
	Camera *camera;
	Console *console;
	Player *player;
	Opening *opening;
	Room *room;
	
	//gameisŠÖŒW
	int game_state;
	
};

// ‰Šú‰»‚ğ‚·‚é
Game *Game_Initialize()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout); 
	freopen("CONIN$", "r", stdin);

	Game *self;
	self = new Game();
	self->console = Console_Initialize();
	self->camera = Camera_Initialize(self->console);
	self->room = Room_Initialize();
	self->player = Player_Initialize(self->camera, self->console, self->room);
	self->script = Script_Initialize(self->camera, self->console, self->player, self->room);
	self->opening = Opening_Initialize();
	//gameisŠÖŒW
	self->game_state = 0;
	return self;
}

void game_play_tick(Game *self)
{
	Player_Update( self->player );
	Room_Update( self->room );
	Script_Update( self->script );
	Camera_Update(self->camera);
	Console_Update( self->console );
}

void game_play_draw(Game *self)
{
	Player_Draw( self->player);
	Room_Draw(self->room);
	Script_Draw( self->script );
	Camera_Draw(self->camera);
	Console_Draw( self->console );
}


// “®‚«‚ğŒvZ‚·‚é
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
		game_play_tick(self);
	}
}

// •`‰æ‚·‚é
void Game_Draw(Game *self)
{
	if(self->game_state  == 0)
	{
		Opening_Draw(self->opening);
	}
	else if(self->game_state  == 1)	
	{
		game_play_draw(self);
	}
}

// I—¹ˆ—‚ğ‚·‚é
void Game_Finalize(Game *self )
{
	free(self);
}
