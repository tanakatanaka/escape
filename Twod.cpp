#include "DxLib.h"
#include "Twod.h"

struct Twod
{
	int window;
	int test;
	VECTOR place;
}; 

// ‰Šú‰»‚ğ‚·‚é
Twod *Twod_Initialize(  )
{
	Twod *self;
	self = (Twod *)malloc(sizeof(Twod));
	self->window = LoadGraph( "‰æ‘œ/test.jpg" );
	return self;
}

//test
void Get_twod(Twod *self, int i)
{
	self->test = i;
}


// “®‚«‚ğŒvZ‚·‚é
void Twod_Update( Twod *self )
{
	
}

// •`‰æ‚·‚é
void Twod_Draw( Twod *self)
{
	if(self->test == 8){DrawGraph( 10, 10, self->window, TRUE ) ;}
}

// I—¹ˆ—‚ğ‚·‚é
void Twod_Finalize( Twod *self )
{
    
}
