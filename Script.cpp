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

typedef std::vector<std::string> Words;

Words split(const std::string &str);


struct Condition
{
	//命令条件の構造体
	//管理番号・場所・方角・命令内容・命令対象
	std::string effect_name;
	int area;
	int hougaku;
	std::string order;
	std::string object;
	std::string special;
	bool one_time;
	
};

struct Effect
{
	//命令効果の構造体
	//管理番号・y・効果番号(0:画像表示・1:文字表示)・画像管理番号・画像の名前・文字・画像文字の管理タグ
	std::string name;
	int x;
	int y;
	std::string effect_type;
	//描画関連
	int draw_id;
	std::string draw_name;
	//文字関連
	std::string text;
	//act関連
	Words action;
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
	std::vector<Condition> condition;
	std::vector<Condition> notice;
	std::vector<Effect> effect;
	//
	std::string last_memo;

};

void pack_conditon_words(Script *self, Words &line)
{
	Condition c;

	c.effect_name = line[1].c_str();
	c.area = std::stoi(line[2]);
	c.hougaku = std::stoi(line[3]);
	
	if(line[0] == "con")
	{
		c.order = line[4].c_str();
		c.object = line[5].c_str();

		if(line.size() > 6){ c.special = line[6].c_str(); }
		else{ c.special = "none"; }

		self->condition.push_back(c);
	}
	else if(line[0] == "not")
	{
		c.one_time = true;
		self->notice.push_back(c);
	}

	
}

void pack_effect_words(Script *self, Words &line)
{
	Effect e;
			
	e.name = line[1].c_str();

	if(line[2] == "draw")
	{
		e.effect_type = "draw";
		e.draw_name = line[3].c_str();
		e.draw_id = std::stoi(line[6]);
	}
	else if(line[2] == "text")
	{
		e.effect_type = "text";
		e.text = line[3].c_str();
	}
	else if(line[2] == "act")
	{
		e.effect_type = "act";
		// eff と act は飛ばして記録
		e.action = Words(line.begin() + 2, line.end());
	}

	if(line[2] == "draw" || line[2] == "text")
	{
		e.x = std::stoi(line[4]);
		e.y = std::stoi(line[5]);
	}
	self->effect.push_back(e);
}

int load_script(Script *self, const char *filename)
{
	std::string line; //1行読み込み用
	std::ifstream file(filename); // ファイルを読み込み

	if (file.fail())
	{
		//ファイル読み込みに失敗
		printf("スクリプト %s を読み込めませんでした\n", filename);
		return -1;
	}

	while (std::getline(file, line))
	{
		Words word_line = split(line);
		
		if(word_line.size() > 0)
		{
			// １行をブロックにして構造体に代入
			if(word_line[0] == "con" || word_line[0] == "not")
			{
				pack_conditon_words(self, word_line);
			}
			else if(word_line[0] == "eff")
			{
				pack_effect_words(self, word_line); 	
			}
		}
	}

	return 0;
}

// 初期化をする
Script *Script_Initialize(Camera *camera, Console *console , Player *player, Room *room)
{
	Script *self;
	self = new Script();

	self->camera = camera;
	self->room = room;
	self->mess = Mess_Initialize( );
	self->twod = Twod_Initialize( );
	self->console = console;
	self->player = player;

	self->last_memo = "non";

	printf("\nスクリプト読み込み　開始\n\n");
	if(load_script(self, "tex/script.txt") == -1)
	{
		MessageBox(NULL,"ファイルが読み込みませんでした","ゲームのエラー", 0);
	}

	return self;
}


Words split(const std::string &str)
{
    typedef std::istream_iterator<std::string> I;
    std::istringstream ss(str);
    Words words;
    std::copy(I(ss), I(), std::back_inserter<Words>(words));
    return words;
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
