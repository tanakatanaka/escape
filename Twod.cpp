#include "DxLib.h"
#include "Twod.h"

struct Twod
{
	int window;
	int test;
	VECTOR place;
}; 

// 初期化をする
Twod *Twod_Initialize(  )
{
	Twod *self;
	self = (Twod *)malloc(sizeof(Twod));
	self->window = LoadGraph( "画像/test.jpg" );
	return self;
}

//test
void Get_twod(Twod *self, int i)
{
	self->test = i;
}


// 動きを計算する
void Twod_Update( Twod *self )
{
	
}

// 描画する
void Twod_Draw( Twod *self)
{
	if(self->test == 8){DrawGraph( 10, 10, self->window, TRUE ) ;}
}

// 終了処理をする
void Twod_Finalize( Twod *self )
{
    
}
