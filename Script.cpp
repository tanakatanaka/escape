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
void search_tag(Script *self, std::string tag, bool change);

Words split(const std::string &str);

struct Condition
{
	//���ߏ����̍\����
	//�Ǘ��ԍ��E�ꏊ�E���p�E���ߓ��e�E���ߑΏ�
	std::string effect_name;
	int area;
	int hougaku;
	std::string order;
	std::string object;
	bool on_off;
	std::string tag;


};

struct Effect
{
	//���ߌ��ʂ̍\����
	//�Ǘ��ԍ��Ey�E���ʔԍ�(0:�摜�\���E1:�����\��)�E�摜�Ǘ��ԍ��E�摜�̖��O�E�����E�摜�����̊Ǘ��^�O
	std::string name;
	int x;
	int y;
	std::string effect_type;
	int draw_id; //�`��֘A
	//�����֘A
	std::string text;
	//act�֘A
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
	//���ߍ\���̕ϐ� 
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
		
		if(line.size() > 7)
		{
			if(line[7] == "true"){ c.on_off = true; }
			else{ c.on_off = false; }
			c.tag = line[8];
		}
		self->condition.push_back(c);
	}
	else if(line[0] == "not")
	{
		c.on_off = true;
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
		e.draw_id = std::stoi(line[3]);
	}
	else if(line[2] == "text")
	{
		e.effect_type = "text";
		e.text = line[3].c_str();
	}
	else if(line[2] == "act")
	{
		e.effect_type = "act";
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
	std::string line; //1�s�ǂݍ��ݗp
	std::ifstream file(filename); // �t�@�C����ǂݍ���

	if (file.fail())
	{
		//�t�@�C���ǂݍ��݂Ɏ��s
		printf("�X�N���v�g %s ��ǂݍ��߂܂���ł���\n", filename);
		return -1;
	}

	while (std::getline(file, line))
	{
		Words word_line = split(line);
		
		if(word_line.size() > 0)
		{
			// �P�s���u���b�N�ɂ��č\���̂ɑ��
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
	

	self->last_memo = "non";

	printf("\n�X�N���v�g�ǂݍ��݁@�J�n\n\n");
	if(load_script(self, "tex/script.txt") == -1)
	{
		MessageBox(NULL,"�t�@�C�����ǂݍ��݂܂���ł���","�Q�[���̃G���[", 0);
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

void swit_on_off(Script *self,  Condition &c)
{
	if(c.tag == "un_open")
	{
		c.on_off = false;
		search_tag(self, "open", false);
	}
}

void search_tag(Script *self, std::string tag, int change)
{
	if(tag != "none")
	{
		for(int i = 0; i < (int)self->condition.size(); i++)
		{
			Condition &c = self->condition[i];
			
			if(c.tag == tag)
			{
				if(change == true){ swit_on_off(self, c); }
				else{ c.on_off = true; }
			}
		}
	}
}

void action_match(Script *self, Words &act)
{
	Room_act(self->room, act);
	Player_act(self->player, act);
	
	search_tag( self, Room_get_tag(self->room), false);
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

			if(c.on_off != false && area_match(c, self->player) && condition_match(c , words))
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

		if(area_match(n, self->player) && n.on_off != false)
		{
			call_effect(self, n);
			n.on_off = false;
 		}
	}
}



void decode_command(Script *self)
{
	//�P���ɕ���
	const char *command = console_d_bag(self->console);
		
	if(command != NULL)
	{
		Words words = split(command);
		//�R���\�[���̂ق��ɂ���R�}���h�����O�Ɉړ�
		console_shift_log(self->console);
		//��������word����Ǌ֐��ɂ�����
		word_act(self,words);
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
	
	check_notice(self);
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
    
}
