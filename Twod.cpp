#include "DxLib.h"
#include "Twod.h"
#include <string>
#include <vector>
#include "Pad.h"

struct Image
{
	int	x;
	int y;
	int id;
};

struct Twod
{
	std::vector<Image> image;
	int dx[100];
};

// 初期化をする
Twod *Twod_Initialize()
{
	Twod *self;
	self = new Twod();

	self->dx[0] = LoadGraph( "画像/test.jpg" ) ;
	return self;
}

void Twod_add_image(Twod *self, int x, int y, int id)
{
	Image i;

	if(i.id < 0)
	{
		i.id = id;
		i.x = x;
		i.y = y;
	}
	
	self->image.push_back(i);
}

void twod_erase_image(Twod *self)
{
	for (int i=0; i < self->image.size(); i++)
	{
		self->image[i].id = -1;	
	}
}


// 動きを計算する
void Twod_Update( Twod *self )
{
	if(Pad_Get( KEY_INPUT_DELETE ) == -1)
	{
		twod_erase_image(self);
	}
	
}

// 描画する
void Twod_Draw( Twod *self)
{
	for (int i=0; i < self->image.size(); i++)
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
