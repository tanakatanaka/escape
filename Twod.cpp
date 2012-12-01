#include "DxLib.h"
#include "Twod.h"

//配列は最大1枠まで
#define MAX 1

struct Twod
{
	int window[MAX];
	char tag[MAX];
	int x[MAX];
	int y[MAX];
	int on[MAX];
	

}; 

// 初期化をする
Twod *Twod_Initialize(  )
{
	Twod *self;
	self = (Twod *)malloc(sizeof(Twod));
	self->window[0] = LoadGraph( "画像/test.jpg" );
	self->tag[0] = 'a';
	self->x[0] = 0;
	self->y[0] = 0;
	printf("\nhajime = %c\n",self->tag[0]);
	return self;
}


void Set_tags(Twod *self, char tag, int x, int y)
{
	printf("\nowari = %c\n",tag);
	for(int i = 0; i++ ; i > MAX)
	{
		if(self->tag[i] == tag)
		{
			self->x[i] = x;
			self->y[i] = y;
			self->on[i] = 1;
		}
	}
}

void All_drawg(Twod *self)
{
	
	if(self->on[0] == 1){DrawGraph( self->x[0], self->y[0], self->window[0], TRUE ) ;}
	
}


// 動きを計算する
void Twod_Update( Twod *self )
{
	
}

// 描画する
void Twod_Draw( Twod *self)
{
	All_drawg(self);
}

// 終了処理をする
void Twod_Finalize( Twod *self )
{
    
}
