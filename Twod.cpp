#include "DxLib.h"
#include "Twod.h"
#include "Player.h"
#include <string>
#include <vector>
#include "Pad.h"


struct Image
{
	int	x;
	int y;
	const char *name;
	int id;
};

struct Twod
{
	Player *player;
	std::vector<Image> image;
	std::vector<int> dx;
};

// èâä˙âªÇÇ∑ÇÈ
Twod *Twod_Initialize(Player *player)
{
	Twod *self;
	self = new Twod();
	self->player = player;

	self->dx.push_back( LoadGraph( "meta/o.png" ) );
	self->dx.push_back( LoadGraph( "meta/v.png" ) );
	self->dx.push_back( LoadGraph( "meta/x.png" ) );

	return self;
}

int image_num(std::string name)
{
	printf("\n name = %s \n",name.c_str());

	if(name == "o"){return 0;}
	else if(name == "v"){return 1;}
	else if(name == "x"){return 2;}

	return -1;
}

void Twod_add_image(Twod *self, int x, int y, const char *name)
{
	Image i;

	printf("\n name = %s \n",name);

	i.x = x;
	i.y = y;
	i.id = image_num(name);

	printf("\n id = %d\n",i.id);
	self->image.push_back(i);
}

void Twod_erase_image(Twod *self)
{
	for (int i=0; i < self->image.size(); i++)
	{
		self->image[i].id = -1;	
	}
}

void display_time(Twod *self)
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 255 ) ;
	SetFontSize( 30 ) ;

	int time = Player_get_time(self->player);
	int paper = Player_get_paper(self->player);
	int area = Player_get_area(self->player);
	int hougaku = Player_get_hougaku(self->player);
	
	DrawFormatString( 490, 30, GetColor( 255, 0, 0 ), "%s", "Time");
	DrawFormatString( 590, 30, GetColor( 255, 0, 0 ), "%d", time);
	DrawFormatString( 490, 60, GetColor( 255, 255, 0 ), "%s", "Paper");
	DrawFormatString( 625, 60, GetColor( 255, 255, 0 ), "%d", paper);
	DrawFormatString( 560, 90, GetColor( 0, 255, 0 ), "%d", area);
	DrawFormatString( 590, 90, GetColor( 0, 0, 255 ), "%d", hougaku);
	SetFontSize( 16 ) ;
}


// ìÆÇ´ÇåvéZÇ∑ÇÈ
void Twod_Update( Twod *self )
{
	if(Pad_Get( KEY_INPUT_DELETE ) == -1)
	{
		Twod_erase_image(self);
	}
	
}

void mess_draw(Twod *self)
{
	SetFontSize(16) ;
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 200 );

	for (int i=0; i < self->image.size(); i++)
	{
		if(self->image[i].id != -1)
		{
			DrawGraph(self->image[i].x, self->image[i].y, self->dx[self->image[i].id], TRUE );
		}
	}
}

// ï`âÊÇ∑ÇÈ
void Twod_Draw( Twod *self)
{
	mess_draw(self);
	display_time(self);
}

// èIóπèàóùÇÇ∑ÇÈ
void Twod_Finalize( Twod *self )
{
    InitGraph( ) ;
	delete self;
}
