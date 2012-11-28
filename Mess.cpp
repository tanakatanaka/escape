#include "string.h"
#include "DxLib.h"
#include "Mess.h"

//���b�Z�[�W�̃t�H���g�̑傫��
#define MESSAGE_FONT_SIZE 20
//���z�o�b�t�@�̍ő啶����
#define MESSAGE_MAX_LENGTH 30
//���z�o�b�t�@�̍ő�s��
#define MESSAGE_MAX_LINE 5
//���b�Z�[�W�{�b�N�X��X���W
#define MESSAGE_BOX_X_POS 40
//���b�Z�[�W�{�b�N�X��Y���W
#define MESSAGE_BOX_Y_POS 340

struct Mess
{
   char g_message[MESSAGE_MAX_LENGTH * MESSAGE_MAX_LINE];
   int g_currentCursor;
   int g_currentLineCursor;
};

// ������������
Mess *Mess_Initialize()
{
	Mess *self;
	self = (Mess *)malloc(sizeof(Mess));
	
	strcpy(self->g_message,"�͂�[hello��[���World�����������������������������������ĂƂ�" \
	"�ɂʂ˂̂͂Ђӂւق܂݂ނ߂��������������");
	

	self->g_currentCursor = 0;
	self->g_currentLineCursor = 0;

	return self;
}

//code �����{��ł��邩���肷��
//�߂�l 1:���{�� 0:���{��ł͂Ȃ�
int isJapaneseCharacter(unsigned char code)
{
	if( (code >= 0x81 && code <= 0x9F) || 
		(code >= 0xE0 && code <= 0xFC) ) {
			return 1;
	}
	return 0;
}

//message�Ŏw�肵�����͂� start �̈ʒu���� len �������\������
void writeSubstring(char* message, int start, int len, int posX, int posY, int color, int bufferLine)
{
	int i;
	char g_messageBuffer[MESSAGE_MAX_LINE][MESSAGE_MAX_LENGTH];
	//������
	int maxLen = strlen( message );
	
	//start�̈ʒu��ύX����
	//start�̈ʒu�܂łɓ��{�ꂪ�łĂ��Ă�����C1�𑫂��Ă���
	for( i = 0; i < start && message[i] != '\0'; ) {
		if( isJapaneseCharacter( message[i] ) ) {
			//���{��̏ꍇ�C2�o�C�g�������߂�
			i += 2;
			//start��1�o�C�g������
			start++;
		}else {
			//���p�����̏ꍇ�C1�o�C�g���i�߂�
			i++;
		}
	}

	//start�̈ʒu���\���������ő啶�������傫���ꍇ
	if( start >= maxLen ) {
		return;
	}

	//�w�肵���ʒu����len�������\������
	for( i = 0; i < len && message[ start + i ] != '\0'; ) {
		if( isJapaneseCharacter( message[ start + i ] ) ) {
			//���{��̏ꍇ�C2������buffer�ɃZ�b�g
			g_messageBuffer[ bufferLine ][ i ] = message[ start + i ];
			g_messageBuffer[ bufferLine ][ i + 1 ] = message[ start + i + 1 ];
			//len�͓��{��Ȃ̂ŁC1�o�C�g���ǉ�����
			len++;
			//2�o�C�g���i�߂�
			i += 2;
		}else {
			//���p����1�������Z�b�g
			g_messageBuffer[ bufferLine ][ i ] = message[ start + i ];
			//1�o�C�g���i�߂�
			i++;
		}
	}
	g_messageBuffer[ bufferLine ][i] = '\0';

	//���b�Z�[�W�`��
	DrawString(posX, posY, g_messageBuffer[ bufferLine ], color );
}

void drawMessage(Mess *self)
{
	int i;
	int g_whiteColor = GetColor(255,255,255);//��
	int g_blackColor = GetColor(0, 0, 0);//��

	if( self->g_message[self->g_currentCursor] != '\0' ) {
		self->g_currentCursor++;
	}

	//MESSAGE_MAX_LENGTH �܂ŕ�����`�悵����i����؂�ւ���
	if(self->g_currentCursor % MESSAGE_MAX_LENGTH == 0 ) {
		if( self->g_message[self->g_currentCursor] != '\0' ) {
			self->g_currentLineCursor++;
		}
	}

	//���b�Z�[�W�`�敔��
	for( i = 0; i < MESSAGE_MAX_LINE; i++ ) {
		if( i == self->g_currentLineCursor ) {
			//���b�Z�[�W���ɕ\��
			writeSubstring( self->g_message, i * MESSAGE_MAX_LENGTH , self->g_currentCursor - MESSAGE_MAX_LENGTH * i,
				MESSAGE_BOX_X_POS + 15, MESSAGE_BOX_Y_POS + MESSAGE_FONT_SIZE * i + 15, g_blackColor, i );
			break;
		}else {
			//���b�Z�[�W�����̂܂ܕ\��
			writeSubstring( self->g_message, i * MESSAGE_MAX_LENGTH , MESSAGE_MAX_LENGTH, MESSAGE_BOX_X_POS + 15,
				MESSAGE_BOX_Y_POS + MESSAGE_FONT_SIZE * i + 15, g_blackColor, i );
		}
	}
}



// �������v�Z����
void Mess_Update( Mess *self )
{
	

	
}		

// �`�悷��
void Mess_Draw( Mess *self)
{
	drawMessage(self);
	Sleep( 100 );
	
}

// �I������������
void Mess_Finalize( Mess *self )
{
    
}