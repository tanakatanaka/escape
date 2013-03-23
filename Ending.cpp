#include "DxLib.h"
#include "Pad.h"
#include "Player.h"
#include "Ending.h"

struct Ending
{
	Player *player;
	int state;
	int game_mode;
	int blink;
}; 

// 初期化をする
Ending *Ending_Initialize(Player *player)
{
	Ending *self;
	self = new Ending();
	self->player = player;
	self->state = 0;
	self->game_mode = 0;
	self->blink = 0; 

	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 255 ) ;

	return self;
}

int Ending_get_next( Ending *self )
{
	//1:opへ
	//0:ゲーム終了 
	//-1：何もしない 

	if(self->state == 2)
	{
		if( self->game_mode % 2 == 0)
		{
			return 1;
		}
		else if( self->game_mode % 2 == 1)
		{
			return 0;
		}
	}
	return -1;
}

static int senter_x(std::string &src, int size)
{
	int x = src.size() * size * 0.5;
	return (640 - x) / 2; 
}

void result_moji_display(Ending *self)
{ 
	SetFontSize( 30 ) ;
	std::string src = "リザルト";

	DrawFormatString( senter_x(src, 30), 50, GetColor( 255, 20, 255 ), "%s", src.c_str()); 
}

static void enter_display(Ending *self)
{ 
	int size = 20;
	SetFontSize( size ) ;
	std::string src = "Enter key を押してください";
	
	if(self->blink % 100 < 80)
	{ 
		DrawFormatString( senter_x(src, size), 400, GetColor( 255, 20, 255 ), "%s", src.c_str()); 
	}
}

static void mode_display(Ending *self)
{ 
	int size = 20;
	SetFontSize( size ) ;

	std::string src1 = "タイトルにもどる";
	std::string src2 = "ゲームをやめる";

	if(self->game_mode % 2 == 0)
	{
		DrawFormatString( senter_x(src1, size), 380, GetColor( 20, 20, 255 ), "%s", src1.c_str()); 
		DrawFormatString(senter_x(src2, size), 410, GetColor( 255, 255, 255 ), "%s", src2.c_str()); 
	}
	else
	{
		DrawFormatString(  senter_x(src1, size), 380, GetColor( 255, 255, 255 ), "%s", src1.c_str()); 
		DrawFormatString( senter_x(src2, size), 410, GetColor( 20, 20, 255 ), "%s", src2.c_str()); 
	}
}


// 動きを計算する
void Ending_Update( Ending *self )
{
	if(self->state == 0)
	{
		enter_display(self);
	}
	else if(self->state == 1)
	{
		if(Pad_Get( KEY_INPUT_UP ) == -1){self->game_mode++;}
		else if(Pad_Get( KEY_INPUT_DOWN ) == -1){self->game_mode--;}
	}

	if( Pad_Get( KEY_INPUT_RETURN ) == -1){self->state++;}
	self->blink++;
}

// 描画する
void Ending_Draw( Ending *self)
{
	result_moji_display(self);
	
	if(self->state == 0)
	{
		enter_display(self);
	}
	else if(self->state == 1)
	{
		mode_display(self);
	}
}

// 終了処理をする
void Ending_Finalize( Ending *self )
{
	
}
