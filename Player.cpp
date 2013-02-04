#include "DxLib.h"
#include "Pad.h"
#include "Camera.h"
#include "Console.h"
#include "Player.h"

struct Player
{
    int area;
    int hougaku;
	Camera *camera;
	Console *console;
	int count;
}; 

// ������������
Player *Player_Initialize(Camera *camera, Console *console)
{
	Player *self;
	self = new Player();
	
	self->camera = camera;
	self->console = console;
	//player�p
	self->hougaku = 0;
	self->area = 0;
	self->count = 30;

	return self;
}

int Player_get_area(Player *self)
{
	return self->area;
}

int Player_get_hougaku(Player *self)
{
	return self->hougaku;
}


void move_area(Player *self)
{
	if(self->hougaku == 0)
	{
		if(self->area > -1 && self->area < 3 ){self->area++;}
		else if(self->area > 5 && self->area < 8 ){self->area--;}
	}
	else if(self->hougaku == 1){if(self->area > 2 && self->area < 5 ){self->area++;}}
	else if(self->hougaku == 2)
	{
		if(self->area > 4 && self->area < 7 ){self->area++;}
		else if(self->area > 1 && self->area < 4 ){self->area--;}
	}
	else if(self->hougaku == 3){if(self->area > 3 && self->area < 6 ){self->area--;}}

	Camera_set_area(self->camera, self->area);
}

void moving( Player *self )
{
	if(self->count > 30 && Pad_Get( KEY_INPUT_UP ) == -1)
	{
		self->count = 0;
		move_area(self);
	}
}

// �������v�Z����
void Player_Update( Player *self )
{
	if(Console_is_input(self->console)  == 0)
	{
		//���s�������̓J����������
		if(Camera_is_look_at(self->camera) == 0)
		{
			moving(self);//���s��� 
		}
	}

	if(Pad_Get( KEY_INPUT_L ) == -1){ printf("\n hougaku = %d \n",self->hougaku); }

	self->hougaku = Camera_set_hougaku(self->camera, 0);
	self->count++;
}

// �`�悷��
void Player_Draw( Player *self)
{
    
}

// �I������������
void Player_Finalize( Player *self )
{
    
}
