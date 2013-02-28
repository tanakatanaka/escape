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

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

struct Script
{
	Room *room;
	Camera *camera;
	Mess *mess;
	Twod *twod;
	Console *console;
	Player *player;
  lua_State *lua;
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
	
	fprintf(stderr, "a\n");
	
	self->lua = luaL_newstate();
	luaL_openlibs(self->lua);
	
  if (luaL_loadfile(self->lua, "script\\script.lua") == LUA_ERRFILE)
  {
		  MessageBox(NULL, "script/script.lua ���ǂݍ��߂܂���ł���", "�Q�[���̃G���[", 0);
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
		//�R���\�[���̂ق��ɂ���R�}���h�����O�Ɉړ�
		console_shift_log(self->console);
		//��������word����Ǌ֐��ɂ�����
	}
}

// �������v�Z����
void Script_Update( Script *self )
{
	Mess_Update( self->mess );
	Twod_Update( self->twod );

	if( Console_is_input(self->console) == 1 && Pad_Get( KEY_INPUT_RETURN ) == -1)
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
    lua_close(self->lua);
}
