#include "DxLib.h"
#include "Pad.h"
#include <string>
#include "Opening.h"
#include "Sound.h"

#define PHI DX_PI_F

struct Opening
{
	 Sound *sound;
     int room;
	 int paper;
	 double plus;
	 int state;
	 int game_mode;
	 int blink;
};

// ������������
Opening *Opening_Initialize( Sound *sound )
{
	Opening *self;
	self = new Opening();
	self->room = MV1LoadModel("meta/op.mqo") ;    //model�摜�n���h���̊i�[
	self->paper = LoadGraph( "meta/paper.png") ;
	self->sound = sound;
	self->plus = 0;
	self->state = 1;
	self->game_mode = 0;
	self->blink = 0;

	SetFontSize( 30 ) ;
	return self;
}

int Opening_get_game_mode(Opening *self)
{
	//1:�Q�[���v���C
	//0:�Q�[���I�� -
	//1�F�������Ȃ�

	if(self->state == 3 )
	{
		if(self->game_mode % 2 == 0){ return 1; }
		return 0;
	}
	return -1;
}

static int center_x(const char *src)
{
	int x = GetDrawStringWidth( src , strlen( src ) ) ;
	return (640 - x) / 2; 
}


static void mode_display(Opening *self)
{ 
	const char *src1 = "�Q�[�����͂��߂�";
	const char *src2 = "�Q�[������߂�";

	int size = GetDrawStringWidth( src1 , strlen( src1 ) );

	DrawModiGraph( center_x(src1) - 20, 360, center_x(src1) + size + 20, 360, 
		center_x(src1) + size + 5, 470, center_x(src1) - 5, 470,self->paper , TRUE );

	if(self->game_mode % 2 == 0)
	{
		DrawFormatString( center_x(src1), 380, GetColor( 20, 20, 255 ), "%s", src1); 
		DrawFormatString(center_x(src2), 410, GetColor( 255, 255, 255 ), "%s", src2); 
	}
	else
	{
		DrawFormatString(  center_x(src1), 380, GetColor( 255, 255, 255 ), "%s", src1); 
		DrawFormatString( center_x(src2), 410, GetColor( 20, 20, 255 ), "%s", src2); 
	}
}

static void moji_display(Opening *self, const char *src, int y, int moji_size = 30)
{ 
	SetFontSize( moji_size ) ;

	int size = GetDrawStringWidth( src , strlen( src ) );
	DrawModiGraph( center_x(src) - 5, y - 40, center_x(src) + size + 5, y - 40, 
		center_x(src) + size + 20, y + 70, center_x(src) - 20, y + 70,self->paper , TRUE );
	DrawFormatString( center_x(src), y, GetColor( 20, 20, 255 ), "%s", src); 	
	
	SetFontSize( 30 ) ;
}

// �������v�Z����
void Opening_Update( Opening *self )
{
	if(self->state == 1)
	{
		self->plus += PHI / 180.0f;

		if(Pad_Get( KEY_INPUT_UP ) == -1)
		{
			Sound_se( self->sound, "selection");
			self->game_mode++;
		}
		else if(Pad_Get( KEY_INPUT_DOWN ) == -1)
		{
			Sound_se( self->sound, "selectionselect");
			self->game_mode--;
		}
	}
	else if(self->state == 2){self->state++;}

	if(self->state < 2 && Pad_Get(KEY_INPUT_RETURN) == 1)
	{
		Sound_se( self->sound, "decide");
		self->state++;
	}
	
	self->blink++;
}

// �`�悷��
void Opening_Draw( Opening *self)
{
	SetCameraPositionAndTarget_UpVecY(VGet( 1000, 1600, 0 ), VGet( 0, 0, 0 ) );
	//���f���֌W
	MV1SetRotationXYZ( self->room, VGet( 0.0f, self->plus / 2, 0.0f ) );
	MV1DrawModel(self->room);
	
	moji_display(self, "�E�o�Q�[���I��", 100, 40);
	if(self->state == 1){ mode_display(self);}
	else if(self->state == 2 && self->game_mode % 2 == 0){ moji_display(self, "���[�h���Ă��܂�", 400);}
}

// �I������������
void Opening_Finalize( Opening *self )
{
	SetFontSize( 16 );
	InitGraph( ) ;
	MV1DeleteModel(self->room);
    delete self;
}
