#include "DxLib.h"
#include "Game_play.h"
#include "Console.h"
#include "Script.h"
#include "Pad.h"
#include "Opening.h"
#include "Player.h"
#include "Room.h"
#include "Sound.h"
#include "Ending.h"
#include "Back.h"


struct Game_play
{
	Back *back;
	Script *script;
	Camera *camera;
	Console *console;
	Player *player;
	Room *room;
	Sound *sound;
};

// ‰Šú‰»‚ð‚·‚é
Game_play *Game_play_Initialize(Sound *sound)
{
	Game_play *self;
	self = new Game_play();
	self->sound = sound;
	self->console = Console_Initialize(self->sound);
	self->camera = Camera_Initialize(self->console);
	self->back = Back_Initialize(self->camera);
	self->room = Room_Initialize();
	self->player = Player_Initialize(self->camera, self->console, self->room, self->sound);
	self->script = Script_Initialize(self->camera, self->console, self->player, self->room, self->sound);

	return self;
}

Player *Game_play_get_result(Game_play *self)
{
	if (Player_get_time(self->player) == 0 || Player_get_end(self->player)) {return self->player;}
	else{return NULL;}
}

// “®‚«‚ðŒvŽZ‚·‚é
void Game_play_Update(Game_play *self)
{
	Back_Update( self->back );
	Player_Update( self->player );
	Room_Update( self->room );
	Script_Update( self->script );
	Camera_Update(self->camera);
	Console_Update( self->console );
}

// •`‰æ‚·‚é
void Game_play_Draw(Game_play *self)
{
	Back_Draw( self->back );
	Camera_Draw(self->camera);
	Room_Draw(self->room);
	Script_Draw( self->script );
	Console_Draw( self->console );
}

// I—¹ˆ—‚ð‚·‚é
void Game_play_Finalize(Game_play *self )
{
	Back_Finalize(self->back);
	Player_Finalize(self->player);
	Room_Finalize(self->room);
	Script_Finalize( self->script );
	Camera_Finalize(self->camera);
	Console_Finalize( self->console );
	delete self;
}
