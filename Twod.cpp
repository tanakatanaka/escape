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
	int dx[100];
};

// ‰Šú‰»‚ğ‚·‚é
Twod *Twod_Initialize(Player *player)
{
	Twod *self;
	self = new Twod();
	self->player = player;

	self->dx[0] = LoadGraph( "‰æ‘œ/test.jpg" ) ;
	self->dx[1] = LoadGraph( "meta/o.png" ) ;
	self->dx[2] = LoadGraph( "meta/v.png" ) ;
	self->dx[3] = LoadGraph( "meta/x.png" ) ;
	return self;
}

int image_num(std::string name)
{
	printf("\n name = %s \n",name.c_str());

	if(name == "test"){return 0;}
	else if(name == "o"){return 1;}
	else if(name == "v"){return 2;}
	else if(name == "x"){return 3;}

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
	int time = Player_get_time(self->player);
	int area = Player_get_area(self->player);
	int hougaku = Player_get_hougaku(self->player);

	SetFontSize( 30 ) ;
	DrawFormatString( 590, 30, GetColor( 255, 0, 0 ), "%d", time); 
	DrawFormatString( 590, 60, GetColor( 0, 255, 0 ), "%d", area);
	DrawFormatString( 590, 90, GetColor( 0, 0, 255 ), "%d", hougaku);
	SetFontSize( 16 ) ;
}


// “®‚«‚ğŒvZ‚·‚é
void Twod_Update( Twod *self )
{
	if(Pad_Get( KEY_INPUT_DELETE ) == -1)
	{
		Twod_erase_image(self);
	}
	
}

// •`‰æ‚·‚é
void Twod_Draw( Twod *self)
{
	for (int i=0; i < self->image.size(); i++)
	{
		if(self->image[i].id != -1)
		{
			DrawGraph(self->image[i].x, self->image[i].y, self->dx[self->image[i].id], TRUE );
		}
	}

	display_time(self);
}

// I—¹ˆ—‚ğ‚·‚é
void Twod_Finalize( Twod *self )
{
    
}
