#include "DxLib.h"
#include "Twod.h"


struct Image
{
	int	x;
	int y;
	int id;
	char tag[100];

};

struct Twod
{
	Image image[100];
	int dx[100];
};

// 初期化をする
Twod *Twod_Initialize()
{
	Twod *self;
	self = (Twod *)malloc(sizeof(Twod));
	for(int i = 0; i < 100;i++)
	{
		self->image[i].id  = -1;
	}
	self->dx[0] = LoadGraph( "画像/test.jpg" ) ;
	return self;
}

void Twod_add_image(Twod *self, int x, int y, int id, const char *tag)
{
	for (int i=0; i < 100; i++)
	{
		if(self->image[i].id < 0)
		{
			self->image[i].id = id;
			self->image[i].x = x;
			self->image[i].y = y;
			strcpy(self->image[i].tag, tag);
			break;
		}
	}
}

void twod_erase_image(Twod *self, const char *tag)
{
	for (int i=0; i < 100; i++)
	{
		if (strcmp(self->image[i].tag, tag) == 0)
		{
			self->image[i].id = -1;
			break;
		}
	}
}


// 動きを計算する
void Twod_Update( Twod *self )
{
	
}

// 描画する
void Twod_Draw( Twod *self)
{
	for (int i=0; i < 100; i++)
	{
		if(self->image[i].id != -1)
		{
			DrawGraph(self->image[i].x, self->image[i].y, self->dx[self->image[i].id], TRUE );
		}
	}
}

// 終了処理をする
void Twod_Finalize( Twod *self )
{
    
}
