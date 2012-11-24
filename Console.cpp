#include "DxLib.h"
#include "Console.h"




struct Console
{
	int cr ;
	int win_s;
	int win_count;
	char bag [20];
}; 

// ‰Šú‰»‚ğ‚·‚é
Console *Console_Initialize()
{
	Console *self;
	self = (Console *)malloc(sizeof(Console));
	self->cr = GetColor( 0 , 0 , 200 ) ;
	self->win_s = 0;
	self->win_count = 0;
	return self;
}

 void Console_sw(Console *self)
 {
	 if(CheckHitKey(KEY_INPUT_ESCAPE) == 1 && self->win_count > 10)
	{
		self->win_s++;
		self->win_count = 0;
	}
 }

 
// “®‚«‚ğŒvZ‚·‚é
void Console_Update( Console *self )
{
	Console_sw(self);

	if(self->win_s % 2 == 1)
	{
		KeyInputSingleCharString( 0 , 420 , 30 , self->bag , TRUE ) ;
		
	}

	self->win_count++;
}

// •`‰æ‚·‚é
void Console_Draw( Console *self)
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 ) ;
	if(self->win_s % 2 == 0){DrawBox( 0, 420 , 640 , 480, self->cr, TRUE) ;}
	else{DrawBox( 0, 380 , 640 , 480, self->cr, TRUE) ;}
}

// I—¹ˆ—‚ğ‚·‚é
void Console_Finalize( Console *self )
{
    
}
