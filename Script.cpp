#include "DxLib.h"
#include <string>
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
typedef std::istream_iterator<std::string> I;
using std::istringstream;
using std::copy;

Words split(const std::string &str);


struct Condition_order
{
	//���ߏ����̍\����
	//�Ǘ��ԍ��E�ꏊ�E���p�E���ߓ��e�E���ߑΏ�

	int num;
	int area;
	int hougaku;
	std::string order;
	std::string object;
	std::string special;
};

struct Effect_order
{
	//���ߌ��ʂ̍\����
	//�Ǘ��ԍ��Ex�Ey�E���ʔԍ�(0:�摜�\���E1:�����\��)�E�摜�̖��O�E�����E�摜�����̊Ǘ��^�O
	int num;
	int x;
	int y;
	int effect_num;
	std::string draw_name;
	std::string text;
	std::string tag;

};

struct Script
{

	Room *room;
    Camera *camera;
    Mess *mess;
	Twod *twod;
	Console *console;

	//���ߍ\���̕ϐ� 
	std::vector<Condition_order> condition_order;
	std::vector<Effect_order> effect_order;
	int condition_count;
	int effect_count;
	
};

void pack_words(Script *self, Words &line)
{
	if(line.size() > 0)
	{
		if(line[0].c_str() == "con")
		{
			self->condition_order[self->condition_count].num = std::stoi(line[1]);
			self->condition_order[self->condition_count].area = std::stoi(line[2]);
			self->condition_order[self->condition_count].hougaku = std::stoi(line[3]);
			self->condition_order[self->condition_count].order = line[4].c_str();
			self->condition_order[self->condition_count].object = line[5].c_str();

			if(line.size() > 6)
			{
				self->condition_order[self->condition_count].special = line[6].c_str();
			}

			self->condition_count++;
		}
		else if(line[0].c_str() == "eff")
		{
			self->effect_order[self->effect_count].num = std::stoi(line[1]);

			if(line[2].c_str() == "draw")
			{
				self->effect_order[self->effect_count].draw_name = line[3].c_str();
			}
			else if(line[2].c_str() == "text")
			{
				self->effect_order[self->effect_count].text = line[3].c_str();
			}

			self->effect_order[self->effect_count].x = std::stoi(line[4]);
			self->effect_order[self->effect_count].y = std::stoi(line[5]);
			self->effect_order[self->effect_count].tag = line[6].c_str();

			self->effect_count++;
		}

	}

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
		pack_words(self, split(line)); // �P�s���u���b�N�ɂ��č\���̂ɑ��
	}

	return 0;
}



// ������������
Script *Script_Initialize(Camera *camera, Console *console , Player *player)
{
	Script *self;
	self = new Script();

	self->camera = camera;
	self->room = Room_Initialize();
	self->mess = Mess_Initialize( );
	self->twod = Twod_Initialize( );
	self->console = console;

	self->condition_count = 0;
	self->effect_count = 0;

	printf("\n�X�N���v�g�ǂݍ��݁@�J�n\n\n");
	load_script(self, "tex/script.txt");

	return self;
}


Words split(const std::string &str)
{
    istringstream ss(str);
    Words words;
    copy(I(ss), I(), std::back_inserter<Words>(words));
    return words;
}

void word_act(Script *self, Words &words)
{	

}

void decode_command(Script *self)
{
	if(Pad_Get( KEY_INPUT_RETURN ) == -1)
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
}


// �������v�Z����
void Script_Update( Script *self )
{
	Room_Update( self->room );
	Mess_Update( self->mess );
	Twod_Update( self->twod );

	decode_command(self);

	
}	

// �`�悷��
void Script_Draw( Script *self)
{
	
	Room_Draw(self->room);
	Twod_Draw( self->twod );
	Mess_Draw(self->mess);
	
}

// �I������������
void Script_Finalize( Script *self )
{
    
}
