#include "DxLib.h"
#include "Twod.h"
#include <string>
#include <vector>

struct Image
{
	int	x;
	int y;
	int id;
	std::string tag;

};

struct Twod
{
	std::vector<Image> image;
	int dx[100];
};

// ‰Šú‰»‚ğ‚·‚é
Twod *Twod_Initialize()
{
	Twod *self;
	self = new Twod();

	self->dx[0] = LoadGraph( "‰æ‘œ/test.jpg" ) ;
	return self;
}

void Twod_add_image(Twod *self, int x, int y, int id, const char *tag)
{
	Image i;

	if(i.id < 0)
	{
		i.id = id;
		i.x = x;
		i.y = y;
		i.tag = tag;
	}
	
	self->image.push_back(i);
}

void twod_erase_image(Twod *self, const char *tag)
{
	for (int i=0; i < self->image.size(); i++)
	{
		if(self->image[i].tag == tag)
		{
			self->image[i].id = -1;
			break;
		}
	}
}


// “®‚«‚ğŒvZ‚·‚é
void Twod_Update( Twod *self )
{
	
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
}

// I—¹ˆ—‚ğ‚·‚é
void Twod_Finalize( Twod *self )
{
    
}
