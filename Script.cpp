#include "DxLib.h"
#include <deque>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <fstream>
#include "Console.h"
#include "Script.h"
#include "Camera.h"
#include "Room.h"
#include "Player.h"
#include "Mess.h"
#include "Twod.h"
#include "Pad.h"
#include "lua_script.h"
#include "Sound.h"

struct Script
{
	Room *room;
	Camera *camera;
	Mess *mess;
	Twod *twod;
	Console *console;
	Player *player;
	Sound *sound;
	LuaScript *lua_script;
	int area;
};

// 初期化をする
Script *Script_Initialize(Camera *camera, Console *console , Player *player, Room *room, Sound *sound)
{
	Script *self;
	self = new Script();

	self->camera = camera;
	self->room = room;
	self->player = player;
	self->mess = Mess_Initialize( );
	self->twod = Twod_Initialize( self->player );
	self->console = console;
	self->sound = sound;
	
	self->area = -100;
	self->lua_script = LuaScript_Initialize();
	
	LuaScript_Set(self->lua_script, "Player", "player", self->player);
	LuaScript_Set(self->lua_script, "Twod", "twod", self->twod);
	LuaScript_Set(self->lua_script, "Mess", "mess", self->mess);
	LuaScript_Set(self->lua_script, "Room", "room", self->room);
	LuaScript_Set(self->lua_script, "Console", "console", self->console);
	LuaScript_Set(self->lua_script, "Sound", "sound", self->sound);

	if (!LuaScript_Load(self->lua_script, "script/script.lua"))
	{
	    exit(1);
	}
	
	return self;
}

void decode_command(Script *self)
{
	//単語後に分解
	const char *command = console_d_bag(self->console);
		
	if(command != NULL)
	{
		//分解したwordを解読関数にかける
		// Luaのon_command関数を呼び出す
		LuaScript_Call(self->lua_script, "on_command");
		//コンソールのほうにあるコマンドをログに移動
		console_shift_log(self->console);
	}
}

void on_move(Script *self)
{
	if(self->area != Player_get_area(self->player))
	{
		LuaScript_Call(self->lua_script, "on_move");
	}

	self->area = Player_get_area(self->player);
}

// 動きを計算する
void Script_Update( Script *self )
{
	Mess_Update( self->mess );
	Twod_Update( self->twod );

	if (Console_is_input(self->console) == 1 && (Pad_Get( KEY_INPUT_RETURN ) == -1 || Pad_Get(KEY_INPUT_NUMPADENTER) == -1))
	{
		decode_command(self);
	}
	
	on_move(self);
}

// 描画する
void Script_Draw( Script *self)
{
	Twod_Draw( self->twod );
	Mess_Draw(self->mess);
	
}

// 終了処理をする
void Script_Finalize( Script *self )
{
    LuaScript_Finalize(self->lua_script);
}
