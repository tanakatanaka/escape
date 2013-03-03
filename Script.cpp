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
#include "Compiler.h"
#include "lua_script.h"

struct Script
{
	Room *room;
	Camera *camera;
	Mess *mess;
	Twod *twod;
	Console *console;
	Player *player;
	LuaScript *lua_script;
};

// ������������
Script *Script_Initialize(Camera *camera, Console *console , Player *player, Room *room)
{
	Script *self;
	self = new Script();

	self->camera = camera;
	self->room = room;
	self->player = player;
	self->mess = Mess_Initialize( );
	self->twod = Twod_Initialize( self->player );
	self->console = console;
	
	self->lua_script = LuaScript_Initialize();
	
	LuaScript_Set(self->lua_script, "Player", "player", self->player);
	LuaScript_Set(self->lua_script, "Twod", "twod", self->twod);
	LuaScript_Set(self->lua_script, "Mess", "mess", self->mess);
	LuaScript_Set(self->lua_script, "Room", "room", self->room);


	if (!LuaScript_Load(self->lua_script, "script/setup/strict.lua") ||
	    !LuaScript_Load(self->lua_script, "script/script.lua"))
	{
	    exit(1);
	}
	
	return self;
}


bool area_match(const Condition &c, Player *player)
{
	return c.area == Player_get_area(player) &&
		   c.hougaku == Player_get_hougaku(player);
}

void decode_command(Script *self)
{
	//�P���ɕ���
	const char *command = console_d_bag(self->console);
		
	if(command != NULL)
	{
		//��������word����Ǌ֐��ɂ�����
		// Lua��on_command�֐����Ăяo��
		LuaScript_Call(self->lua_script, "on_command");
		//�R���\�[���̂ق��ɂ���R�}���h�����O�Ɉړ�
		console_shift_log(self->console);
	}
}

// �������v�Z����
void Script_Update( Script *self )
{
	Mess_Update( self->mess );
	Twod_Update( self->twod );

	if (Console_is_input(self->console) == 1 && Pad_Get( KEY_INPUT_RETURN ) == -1)
	{
		decode_command(self);
	}
	
}

// �`�悷��
void Script_Draw( Script *self)
{
	Twod_Draw( self->twod );
	Mess_Draw(self->mess);
	
}

// �I������������
void Script_Finalize( Script *self )
{
    LuaScript_Finalize(self->lua_script);
}
