#include "DxLib.h"
#include "Twod.h"

//�z��͍ő�1�g�܂�
#define MAX 1

struct Twod
{
	int window[MAX];
	char tag[MAX];
	int x[MAX];
	int y[MAX];
	int on[MAX];
	

}; 

// ������������
Twod *Twod_Initialize(  )
{
	Twod *self;
	self = (Twod *)malloc(sizeof(Twod));
	self->window[0] = LoadGraph( "�摜/test.jpg" );
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


// �������v�Z����
void Twod_Update( Twod *self )
{
	
}

// �`�悷��
void Twod_Draw( Twod *self)
{
	All_drawg(self);
}

// �I������������
void Twod_Finalize( Twod *self )
{
    
}
