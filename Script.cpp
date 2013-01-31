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

//�X�N���v�g�͍ő�1000�s�܂œǂݍ���
#define SCRIPT_MAX_LINE 1000
//�X�N���v�g�ő啶����
#define SCRIPT_MAX_STRING_LENGTH 300

typedef std::vector<std::string> Words;
typedef std::istream_iterator<std::string> I;
using std::istringstream;
using std::copy;



struct Script
{
	Room *room;
    Camera *camera;
    Mess *mess;
	Twod *twod;
	Console *console;
    int maxLineNumber;			//�X�N���v�g�s��
	int currentLine;			//���݉��s�ڂ����s���Ă��邩
	const char* filename;		//�t�@�C����
	char script[SCRIPT_MAX_LINE][SCRIPT_MAX_STRING_LENGTH];
	char *word[10];
	//�v���C���[���
	int area;
	int hougaku;
	//���ߏ��������ϐ� 
	std::vector<int> draw_order;
	std::vector<int> word_order;
};

int loadScript(const char* filename, Script *script);
int decodeScript(const char* scriptMessage, Script *script);
void splitString(const char* src, char* dest[], const char* delim, int splitNum);

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

	self->draw_order.resize(100, 0);
	self->word_order.resize(100, 0);

	printf("\n�X�N���v�g�J�n\n\n");
	loadScript( "tex/script.txt", self );
	return self;
}



//�X�N���v�g�t�@�C����ǂݍ���
//�߂�l -1 : ���s  0 : ����
int loadScript(const char* filename, Script *script)
{
	int pos;
	char c;
	//�X�N���v�g�t�@�C��
	FILE* fp;

	//�X�N���v�g�t�@�C�����J��
	fp = fopen(filename, "r");

	if(fp == NULL )
	{
		//�t�@�C���ǂݍ��݂Ɏ��s
		printf("�X�N���v�g %s ��ǂݍ��߂܂���ł���\n", filename);
		return -1;
	}

	//script�������ݎ��Ɏg�p
	pos = 0;
	for( ;; ) {
		//�ꕶ���ǂݍ���
		c = fgetc( fp );
		//�t�@�C���̏I��肩�ǂ���
		if( feof( fp ) ) {
			break;
		}
		//���͐擪�̋󔒕�����ǂݔ�΂�
		while( (c == ' ' || c == '\t') && pos == 0 && !feof( fp ) ) {
			c = fgetc( fp );
		}
		if( pos >= SCRIPT_MAX_STRING_LENGTH - 1 ) {
			//1�s�̕���������������
			printf("error: ���������������܂� (%d�s��)", script->currentLine );
			return -1;
		}
		//���s�������o�Ă����ꍇ�C���̍s�ֈړ�
		if( c == '\n' ) 
		{
			//��s�͓ǂݔ�΂�
			if( pos == 0 ) 
			{
				continue;
			}
			
			//\0�𕶎���̍Ō�ɕt����
			script->script[ script->currentLine ][ pos ] = '\0';
			//���̍s�Ɉړ�
			script->currentLine++;
			//�������݈ʒu��0�ɂ���
			pos = 0;
		}
		else 
		{
			//��������
			script->script[ script->currentLine ][ pos ] = c;
			//�����������݈ʒu�����炷
			pos++;
			
		}
		
	}
	//�ő�s��
	script->maxLineNumber = script->currentLine;
	//�ǂݍ��ݒ��̍s��0�ɂ���
	script->currentLine = 0;
	//�X�N���v�g�t�@�C������ݒ�
	script->filename = filename;
	return 0;
}

//�����񕪊�(1�s�̍ő啶������ SCRIPT_MAX_STRING_LENGTH)
//src : ����������������
//dest: �������ꂽ������
//delim: ��؂蕶��
//splitNum : �ő啪����
void splitString(const char* src, char* dest[], const char* delim, int splitNum)
{
	int i;
	char* cp;
	char* copySrc;

	//���̕��͂��R�s�[����
	copySrc = (char*)malloc( sizeof(int) * SCRIPT_MAX_STRING_LENGTH + 1);
	strncpy( copySrc, src, SCRIPT_MAX_STRING_LENGTH );
	cp = copySrc;

	//strtok���g���� copySrc ��delim��؂�ŕ�������
	for( i = 0; i < splitNum ; i++ ) {
		//�����Ώە����񂪖����Ȃ�܂ŕ���
		if( (dest[i] = strtok(cp, delim)) == NULL ) {
			break;
		}
		//2��ڂ�strtok���Ăяo�����́Ccp��NULL�ɂ���
		cp = NULL;
	}
	//�������ꂽ������̍Ō�̗v�f��NULL�Ƃ��Ă���
	dest[i] = NULL;
}

//�X�N���v�g������ǂ���
//�߂�l 1: ����  0: ���s
int decodeScript(const char* scriptMessage, Script *self)
{
	//�������ꂽ�X�N���v�g��
	char* message[100];
	//��������p
	char* selectMessage[10];
	char* select[10][2];

	//�����񕪊����̋�؂蕶��
	const char* delim = " ";
	const char* selectDelim = "@@";
	
	//�X�N���v�g����
	splitString( scriptMessage, message, delim, 100 );

	//�����Ɏ��s�����ꍇ
	if( message[0] == NULL ) {
		return 0;
	}

	if(strncmp(message[0], "@@draw", SCRIPT_MAX_STRING_LENGTH) == 0)
	{
		//�摜�`��
		if(self->draw_order[atoi( message[1] )] == -1)
		{
			twod_add_image(self->twod, atoi( message[2] ), atoi( message[3] ), atoi( message[4] ),  message[5]);
			self->draw_order[atoi( message[1] )] = 0;
		}
		return 1;
	}
	else if(strncmp(message[0], "@@word", SCRIPT_MAX_STRING_LENGTH) == 0)
	{
		//�����`��
		if(self->word_order[atoi( message[1] )] == -1)
		{
			mess_add_word(self->mess,atoi( message[2] ), atoi( message[3] ), message[4] , message[5] );
			self->word_order[atoi( message[1] )] = 0;
		}
		return 1;
	}
	else if(strncmp(message[0], "@@reset", SCRIPT_MAX_STRING_LENGTH) == 0)
	{
		return -1;
	}
	else if( strncmp(message[0], "@@label", SCRIPT_MAX_STRING_LENGTH) == 0 ) 
	{
		//���x���̏ꍇ�͂Ȃɂ����Ȃ�
		printf("\ngyou = %d\n",self->currentLine);
		return 1;
	}

	return 1;
}

Words split(const char *str)
{
    istringstream ss(str);
    Words words;
    copy(I(ss), I(), std::back_inserter<Words>(words));
    return words;
}


int area_hougaku(Script *self, int area , int hougaku)
{
	if(self->area == area && self->hougaku == hougaku)
	{
		return 1;
	}

	return 0;
}

void word_act(Script *self, Words &words)
{
	if(words[0] == "check")
	{
		if(words.size() > 1)
		{
			if(words[1] == "door")
			{
				if(area_hougaku(self,0,0))
				{
					self->word_order[0] = -1;
				}
			}
			if(words[1] == "draw")
			{
				if(area_hougaku(self,1,3))
				{	
					self->draw_order[10] = -1;
					self->word_order[10] = -1;
				}
			}
		}
	}

	else if(words[0] == "open")
	{
		if(words.size() > 1)
		{
			if(words[1] == "door")
			{
				if(area_hougaku(self,0,0))
				{
					Room_set_open(self->room, 1);
				}
			}
		}
	}
	

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

void Script_set_area(Script *self, int area)
{
	self->area = area;
}

void Script_set_hougaku(Script *self, int hougaku)
{
	self->hougaku = hougaku;
}


// �������v�Z����
void Script_Update( Script *self )
{
	Camera_Update(self->camera);
	Room_Update( self->room );
	Console_Update( self->console );
	Mess_Update( self->mess );
	Twod_Update( self->twod );

	decode_command(self);

	int state_flag = decodeScript( self->script[ self->currentLine ], self );
	
	if(state_flag == 1)
	{
		//��ʂ̖��ߌ㎟�̍s��
		self->currentLine++;
	}
	else if(state_flag == -1)
	{
		//@@reset�̖��ߌ�0�s�ڂ�
		self->currentLine = 0;
	}

}	

// �`�悷��
void Script_Draw( Script *self)
{
	Camera_Draw(self->camera);
	Room_Draw(self->room);
	Console_Draw( self->console );
	Twod_Draw( self->twod );
	Mess_Draw(self->mess);
	
}

// �I������������
void Script_Finalize( Script *self )
{
    
}
