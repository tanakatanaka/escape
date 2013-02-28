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

typedef std::vector<std::string> Words;

Words split(const std::string &str);

struct State
{
	int a;
	int b;
};

struct Script
{
	Room *room;
	Camera *camera;
	Mess *mess;
	Twod *twod;
	Console *console;
	Player *player;

	//命令構造体変数 
	std::vector<When> when;
	std::vector<Condition> condition;
	std::vector<Condition> notice;
	std::vector<Effect> effect;

	std::string last_memo;
	State state;
};

// 初期化をする
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
	Compiler *compiler = Compiler_Initialize( );
	
	CompilerResult result = Compiler_compile(compiler, "tex/script.txt");

	self->when = result.when;
	self->condition = result.condition;
	self->notice = result.notice;
	self->effect = result.effect;
	self->last_memo = "non";
	self->state.a = 0;
	self->state.b = 0;
	return self;
}


bool area_match(const Condition &c, Player *player)
{
	return c.area == Player_get_area(player) &&
		   c.hougaku == Player_get_hougaku(player);
}

bool condition_match(const Condition &c, Words &words)
{
	return words.size() >= 2 &&
		   c.order == words[0] &&
		   c.object == words[1];
}

void action_match(Script *self, Words &act)
{
	Room_act(self->room, act);
	Player_act(self->player, act);
	
}

void call_effect(Script *self, const Condition &c)
{
	for(int j = 0; j < (int)self->effect.size(); j++)
	{
		if(c.effect_name == self->effect[j].name)
		{
			Effect &e = self->effect[j];

			if(e.effect_type == "draw")
			{
				if(self->last_memo != c.effect_name) 
				{ 
					Twod_erase_image(self->twod);
					self->last_memo = c.effect_name;
				}
				Twod_add_image(self->twod, e.x, e.y, e.draw_id);
			}
			else if(e.effect_type == "text")
			{
				if(self->last_memo != c.effect_name)
				{ 
					Mess_erase_word(self->mess); 
					self->last_memo = c.effect_name;
				}
				Mess_add_word(self->mess, e.x, e.y, e.text.c_str());
			}
			else if(e.effect_type == "act")
			{
				action_match(self, e.action);
			}
		}

	}
	self->last_memo = "non"; 
}

void word_act(Script *self, Words &words)
{	
	if(words.size() > 0)
	{
		for(int i = 0; i < (int)self->condition.size(); i++)
		{
			Condition &c = self->condition[i];

			if(area_match(c, self->player) && condition_match(c , words))
			{
				call_effect(self, c);
			}
		}
	}
}

void check_notice(Script *self)
{	
	for(int i = 0; i < (int)self->notice.size(); i++)
	{
		Condition &n = self->notice[i];

		if(area_match(n, self->player) && n.one_time == true)
		{
			call_effect(self, n);
			n.one_time = false;
 		}
	}
}



void decode_command(Script *self)
{
	//単語後に分解
	const char *command = console_d_bag(self->console);
		
	if(command != NULL)
	{
		Words words = split(command);
		//コンソールのほうにあるコマンドをログに移動
		console_shift_log(self->console);
		//分解したwordを解読関数にかける
		word_act(self,words);
	}
}

// 動きを計算する
void Script_Update( Script *self )
{
	Mess_Update( self->mess );
	Twod_Update( self->twod );

	if( Console_is_input(self->console) == 1 && Pad_Get( KEY_INPUT_RETURN ) == -1)
	{
		decode_command(self);
	}
	
	check_notice(self);
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
    
}
