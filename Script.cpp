#include "DxLib.h"
#include <string.h>
#include <stdlib.h>
#include "Script.h"
#include "Room.h"
#include "Camera.h"
#include "Room.h"
#include "Mess.h"
#include "Twod.h"
#include "Pad.h"
#include "Console.h"


//�X�N���v�g�͍ő�1000�s�܂œǂݍ���
#define SCRIPT_MAX_LINE 1000
//�X�N���v�g�ő啶����
#define SCRIPT_MAX_STRING_LENGTH 300

struct Script
{
	Room *room;
    Camera *camera;
    Mess *mess;
	Twod *twod;
	Console *console;
	int load_flag;
    int maxLineNumber;			//�X�N���v�g�s��
	int currentLine;			//���݉��s�ڂ����s���Ă��邩
	const char* filename;		//�t�@�C����
	char script[SCRIPT_MAX_LINE][SCRIPT_MAX_STRING_LENGTH];
};

int loadScript(const char* filename, Script *script);
int decodeScript(const char* scriptMessage, Script *script);
void splitString(const char* src, char* dest[], const char* delim, int splitNum);

// ������������
Script *Script_Initialize( )
{
	Script *self;
	self = (Script *)calloc(sizeof(Script), 1);

	self->camera = Camera_Initialize( );
	self->room = Room_Initialize();
	self->mess = Mess_Initialize( );
	self->twod = Twod_Initialize( );
	self->console = Console_Initialize( );
	self->load_flag = 1;
	
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

//�w�肵�����x��������s����T��
//�߂�l ���̐�: �w�肵�����x���̍s�ԍ� -1: �G���[
int searchScriptLabel(const char* label, Script *script)
{
	//�������ꂽ�X�N���v�g��
	char* message[100];
	//�����񕪊����̋�؂蕶��
	const char* delim = " ";
	int i, line = -1;

	for( i = 0; i < script->maxLineNumber; i++ ) { 
		//�X�N���v�g����
		splitString( script->script[i] , message, delim, 100 );

		//�����Ɏ��s�����ꍇ
		if( message[0] == NULL ) {
			return -1;
		}

		//�w�肵�����x����T��
		if( strncmp(message[0], "@@label", SCRIPT_MAX_STRING_LENGTH) == 0 ) {
			if( strncmp(message[1], label, SCRIPT_MAX_STRING_LENGTH) == 0 ) {
				//�w�肵�����x��������������
				line = i;
				break;
			}
		}
	}

	return line;
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

//�f�o�b�O�p
//elem�̗v�f��\��
void printElements(char* elem[])
{
	int i;
	for( i = 0; elem[i] != NULL; i++ ) {
		printf("%d : %s\n", i + 1, elem[i] );
	}
}

//�X�N���v�g������ǂ���
//�߂�l 1: ����  0: ���s
int decodeScript(const char* scriptMessage, Script *self)
{
	int i, selectNum, choice, line;
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

	//script�̎d�l
	//
	//@@message ������
	//--- ����������b�Z�[�W�Ƃ��ĕ\������
	//@@select ����1�̏ꍇ@@LABEL1 ����2�̏ꍇ@@LABEL2 ����3�̏ꍇ@@LABEL3
	//--- ��������
	
	//message[0] �� @@message �̎��́C���b�Z�[�W���߂������Ɣ��f
	if( strncmp(message[0], "@@message", SCRIPT_MAX_STRING_LENGTH) == 0 ) 
	{
		printf("���b�Z�[�W : %s\n", message[1] );
	}
	else if( strncmp(message[0], "@@drawgraph", SCRIPT_MAX_STRING_LENGTH) == 0 ) 
	{
		printf("�摜 %s �\�� -- x���W : %d, y���W : %d\n", 
			message[3], atoi( message[1] ), atoi( message[2] ) );
	}
	else if(strncmp(message[0], "@@drawtest", SCRIPT_MAX_STRING_LENGTH) == 0 )
	{
		twod_add_image(self->twod, atoi( message[1] ), atoi( message[2] ), atoi( message[3] ),  message[4] );
	}
	else if(strncmp(message[0], "@@drawerase", SCRIPT_MAX_STRING_LENGTH) == 0 )
	{
		twod_erase_image(self->twod, message[1] );
	}

	else if( strncmp(message[0], "@@select", SCRIPT_MAX_STRING_LENGTH) == 0 ) {

		for(i = 0; message[i + 1] != NULL; i++ ) {
			//�������������͂ƃW�����v���x���Ƃɕ�����
			splitString( message[i + 1], selectMessage, selectDelim, 2 );
			//��������
			select[i][0] = selectMessage[0];
			//���x��
			select[i][1] = selectMessage[1];
		}
		//����
		selectNum = i;

		//�����ŕ������ʂɕ\��
		for(i = 0; i < selectNum; i++) {
			printf("���� %d : %s\n", i + 1, select[i][0] );
		}
		//�����I��
		choice = 0;
		while( choice <= 0 || choice > selectNum ) {
			printf("�I�� :");
			scanf("%d", &choice );
		}

		//���x�������s�ڂɂ��邩���擾
		line = searchScriptLabel( select[choice - 1][1] , self );
		//�w�肵�����x����������Ȃ�����
		if( line == -1 ) {
			printf("�X�N���v�g�G���[:��������̎w�胉�x�����Ԉ���Ă��܂�(%d�s��)\n",
				self->currentLine + 1 );
			return 0;
		}
		//�ǂݎ�蒆�̍s�ԍ������x���̍s�Ɉړ�
		self->currentLine = line;

	}else if( strncmp(message[0], "@@goto", SCRIPT_MAX_STRING_LENGTH) == 0 ) {
		//���x�������s�ڂɂ��邩���擾
		line = searchScriptLabel( message[1], self );
		//�w�肵�����x����������Ȃ�����
		if( line == -1 ) {
			printf("�X�N���v�g�G���[:�w�肵�����x����������܂���ł���(%d�s��)\n",
				self->currentLine + 1);
			return 0;
		}
		//�ǂݎ�蒆�̍s�ԍ������x���̍s�Ɉړ�
		self->currentLine = line;

	}else if( strncmp(message[0], "@@label", SCRIPT_MAX_STRING_LENGTH) == 0 ) {
		//���x���̏ꍇ�͂Ȃɂ����Ȃ�
	}
	

	return 1;
}

// �������v�Z����
void Script_Update( Script *self )
{
	Pad_Update(  );
	Camera_Update(self->camera);
	Room_Update( self->room );
	Console_Update( self->console );
	//Mess_Update( self->mess );
	Twod_Update( self->twod );
	

	if(self->load_flag == 1 && decodeScript( self->script[ self->currentLine ], self ) != 0)
	{
		self->currentLine++;
		self->load_flag = 0;	
	}

	if(Pad_Get(KEY_INPUT_Q) == 1 ){self->load_flag = 1;}

	//for( ; decodeScript( self->script[ self->currentLine ], self ) != 0 ; self->currentLine++ );
	

}

// �`�悷��
void Script_Draw( Script *self)
{
	Room_Draw(self->room);
	Console_Draw( self->console );
	Twod_Draw( self->twod );
	Mess_Draw(self->mess);
	
}

// �I������������
void Script_Finalize( Script *self )
{
    
}
