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


struct Condition_order
{
	//���ߏ����̍\����
	//�Ǘ��ԍ��E�ꏊ�E���p�E���ߓ��e�E���ߑΏ�

	int num;
	int area;
	int hougaku;
	std::string order;
	std::string object;

};

struct Effect_order
{
	//���ߌ��ʂ̍\����
	//x,y,���ʔԍ�(0:�摜�\�� 1:�����\�� 2:����)
	int num;
	int x;
	int y;
	int effect_num;
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
	
};

void pack_words(Script *self, Words one_words)
{
	printf("\n 1 \n");

	for(int i = 0; i < one_words.size() - 1; i++)
	{
		if(one_words[0] == "jojo")
		{
			printf("\n lalala \n");
		}

	}

}

int load_script(Script *self, const char *filename)
{
	int pos = 0; //���݂̕����ʒu
	int now_line = 0; //���݂̍s�ʒu
	int block = 0;	//���݂̃u���b�N�ʒu
	char c; //1����
	std::vector<std::string> one_words;
	FILE* fp; //�X�N���v�g�t�@�C��

	fp = fopen(filename, "r"); //�X�N���v�g�t�@�C�����J��

	if(fp == NULL )
	{
		//�t�@�C���ǂݍ��݂Ɏ��s
		printf("�X�N���v�g %s ��ǂݍ��߂܂���ł���\n", filename);
		return -1;
	}

	while(1) 
	{
		c = fgetc( fp ); //�ꕶ���ǂݍ���
		
		if( feof( fp ) ) { break;} //�t�@�C���̏I��肩�ǂ���
		
		//���͐擪�̋󔒕�����ǂݔ�΂�
		while( (c == ' ' || c == '\t') && pos == 0 && !feof( fp ) ) 
		{
			block++;
			c = fgetc( fp );
		}

		//���s�������ł�܂�
		if( c != '\n' ) 
		{
			one_words[block] += c; //1�P���1�����ǉ�
			pos++;//�����������݈ʒu�����炷
		}
		else 
		{
			//��s�͓ǂݔ�΂�
			if( pos == 0 ) { continue; }

			//���s�������o���玟�̍s��
			//���̍ۂ�,���̍s�̒P��B���l�߂�֐���,�����čs�ʒu�E�����ʒu�E�u���b�N�ʒu�����Z�b�g
			pack_words(self, one_words);
			now_line++; //���̍s�Ɉړ�
			pos = 0; //���݂̕����ʒu��0��
			block = 0; //���݂̃u���b�N��0��
		}
	
	

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

	printf("\n�X�N���v�g�ǂݍ��݁@�J�n\n\n");
	//load_script(self, "tex/script.txt");

	return self;
}





Words split(const char *str)
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
