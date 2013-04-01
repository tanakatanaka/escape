#include "DxLib.h"
#include "Pad.h"
#include "Player.h"
#include "Ending.h"
#include "Sound.h"

struct Ending
{
	Player *player;
	Sound *sound;
	int paper;
	int state;
	int game_mode;
	int blink;
}; 

// ������������
Ending *Ending_Initialize(Player *player, Sound *sound)
{
	Ending *self;
	self = new Ending();
	self->player = player;
	self->sound = sound;
	self->paper = LoadGraph( "meta/paper.png") ;
	self->state = 1;
	self->game_mode = 0;
	self->blink = 0; 
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 255 ) ;

	SetFontThickness(6);

	return self;
}

int Ending_get_next( Ending *self )
{
	//1:op��
	//0:�Q�[���I�� 
	//-1�F�������Ȃ� 

	if(self->state == 2)
	{
		if( self->game_mode % 2 == 0){ return 1; }
		return 0;
	}
	return -1;
}

static int center_x(const char *src)
{
	int x = GetDrawStringWidth( src , strlen( src ) ) ;
	return (640 - x) / 2; 
}

void score_moji_display(Ending *self)
{ 
	SetFontSize( 30 ) ;
	const char *src = "���U���g";

	DrawFormatString( center_x(src), 50, GetColor( 0, 0, 0 ), "%s", src); 
}

void result_display(Ending *self)
{
	int all_score = 0;
	int score = 0;

	SetFontSize( 20 ) ;

	score = Player_get_paper(self->player) * 1000;
	all_score += score;
	const char *src = "����邢 �~ %d = %d";
	DrawFormatString( center_x(src), 100, GetColor( 0, 0, 0 ), src, score / 1000, score); 

	score = Player_get_time(self->player) * 100;
	all_score += score;
	src = "�̂��肶���� �~ %d = %d";
	DrawFormatString( center_x(src), 130, GetColor( 0, 0, 0 ), src, score / 100, score); 
	src = "�X�R�A = %d";
	DrawFormatString( center_x(src), 160, GetColor( 0, 0, 0 ), src, all_score); 
}



static void mode_display(Ending *self)
{ 
	int size = 20;
	SetFontSize( size ) ;

	const char *src1 = "�^�C�g���ɂ��ǂ�";
	const char *src2 = "�Q�[������߂�";

	if(self->game_mode % 2 == 0)
	{
		DrawFormatString( center_x(src1), 380, GetColor( 0, 0, 0 ), "%s", src1); 
		DrawFormatString(center_x(src2), 410, GetColor( 255, 255, 255 ), "%s", src2); 
	}
	else
	{
		DrawFormatString(  center_x(src1), 380, GetColor( 255, 255, 255 ), "%s", src1); 
		DrawFormatString( center_x(src2), 410, GetColor( 0, 0, 0 ), "%s", src2); 
	}
}


// �������v�Z����
void Ending_Update( Ending *self )
{
	if(self->state == 1)
	{
		if(Pad_Get( KEY_INPUT_UP ) == -1)
		{
			Sound_se( self->sound, "selection");
			self->game_mode++;
		}
		else if(Pad_Get( KEY_INPUT_DOWN ) == -1)
		{
			Sound_se( self->sound, "selection");
			self->game_mode--;
		}
	}

	if( Pad_Get( KEY_INPUT_RETURN ) == -1)
	{
		Sound_se( self->sound, "decide");
		self->state++;
	}
	self->blink++;
}

// �`�悷��
void Ending_Draw( Ending *self)
{
	DrawModiGraph( 0, 0, 640, 0, 640, 480, 0, 480, self->paper , TRUE );

	score_moji_display(self);
	result_display(self);

	if(self->state == 1)
	{
		mode_display(self);
	}
}

// �I������������
void Ending_Finalize( Ending *self )
{
	InitGraph( ) ;
	delete self;
}
