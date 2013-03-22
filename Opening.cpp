#include "DxLib.h"
#include "Pad.h"
#include <string>
#include "Opening.h"

struct Opening
{
     int room;
	 double plus;
	 int state;
	 int game_mode;
	 int blink;
}; 

// 初期化をする
Opening *Opening_Initialize( )
{
	Opening *self;
	self = new Opening();
	self->room = MV1LoadModel("meta/room.mqo") ;    //model画像ハンドルの格納
	self->plus = 0;
	self->state = 0;
	self->game_mode = 0;
	self->blink = 0;

	SetFontSize( 30 ) ;
	return self;
}

int Opening_get_game_mode(Opening *self)
{
	//1:ゲームプレイ
	//0:ゲーム終了 -
	//1：何もしない

	if(self->state == 3 )
	{
		if(self->game_mode % 2 == 0)
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

static void enter_display(Opening *self)
{ 
	std::string src = "Enter key を押してください";
	
	if(self->blink % 100 < 80)
	{ 
		DrawFormatString( senter_x(src, 30), 400, GetColor( 255, 20, 255 ), "%s", src.c_str()); 
	}
}

static void mode_display(Opening *self)
{ 
	std::string src1 = "ゲームをはじめる";
	std::string src2 = "ゲームをやめる";

	if(self->game_mode % 2 == 0)
	{
		DrawFormatString( senter_x(src1, 30), 380, GetColor( 20, 20, 255 ), "%s", src1.c_str()); 
		DrawFormatString(senter_x(src2, 30), 410, GetColor( 255, 255, 255 ), "%s", src2.c_str()); 
	}
	else
	{
		DrawFormatString(  senter_x(src1, 30), 380, GetColor( 255, 255, 255 ), "%s", src1.c_str()); 
		DrawFormatString( senter_x(src2, 30), 410, GetColor( 20, 20, 255 ), "%s", src2.c_str()); 
	}
}

void load_display(Opening *self)
{ 
	std::string src = "ロードしています";
	DrawFormatString( senter_x(src, 30), 400, GetColor( 20, 20, 255 ), "%s", "ロードしています"); 	
}

// 動きを計算する
void Opening_Update( Opening *self )
{
	if(self->state == 0)
	{
		self->plus += PHI / 180.0f;
	}
	else if(self->state == 1)
	{
		if(Pad_Get( KEY_INPUT_UP ) == -1){self->game_mode++;}
		else if(Pad_Get( KEY_INPUT_DOWN ) == -1){self->game_mode--;}
		else if(Pad_Get( KEY_INPUT_BACK ) == -1){self->state--;}

	}
	else if(self->state == 2){self->state++;}

	if(self->state < 2 && Pad_Get(KEY_INPUT_RETURN) == 1)
	{
		self->state++;
	}
	
	self->blink++;
}

// 描画する
void Opening_Draw( Opening *self)
{
	SetCameraPositionAndTarget_UpVecY(VGet( 1000, 1600, 0 ), VGet( 0, 0, 0 ) );
	//モデル関係
	MV1SetRotationXYZ( self->room, VGet( 0.0f, self->plus / 2, 0.0f ) );
	MV1DrawModel(self->room);

	DrawBox( 120 , 360 , 540 , 470 ,GetColor( 0, 0, 0 ) , TRUE ) ;

	if(self->state == 0){ enter_display(self);}
	else if(self->state == 1){ mode_display(self);}
	else if(self->state == 2 && self->game_mode % 2 == 0){ load_display(self);}
}

// 終了処理をする
void Opening_Finalize( Opening *self )
{
	SetFontSize( 16 );
	MV1DeleteModel(self->room);
    free(self);
}
