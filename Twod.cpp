#include "DxLib.h"
#include "Twod.h"

struct Twod
{
	int window;
	int test;
	VECTOR place;
}; 

// ������������
Twod *Twod_Initialize(  )
{
	Twod *self;
	self = (Twod *)malloc(sizeof(Twod));
	self->window = LoadGraph( "�摜/test.jpg" );
	return self;
}

//test
void Get_twod(Twod *self, int i)
{
	self->test = i;
}


// �������v�Z����
void Twod_Update( Twod *self )
{
	
}

// �`�悷��
void Twod_Draw( Twod *self)
{
	if(self->test == 8){DrawGraph( 10, 10, self->window, TRUE ) ;}
}

// �I������������
void Twod_Finalize( Twod *self )
{
    
}
