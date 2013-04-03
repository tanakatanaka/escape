#include "DxLib.h"
#include "Pad.h"
#include "Camera.h"
#include "Console.h"
#include "Player.h"
#include "Room.h"
#include "Sound.h"
#include <string>
#include <vector>

#define INTRO -1
#define START 0
#define END 1


// ������������
Player *Player_Initialize(Camera *camera, Console *console, Room *room, Sound *sound)
{
	Player *self;
	self = new Player();
	self->sound = sound;
	self->camera = camera;
	self->console = console;
	self->room = room;
	//player�p
	self->area = 0;
	self->count = 30;
	self->time_limit = 50000;
	self->get_paper = 0;
	self->player_state = -1;

	return self;
}

int Player_get_state(Player *self)
{
	return self->player_state;
}

int Player_get_area(Player *self)
{
	return self->area;
}

int Player_get_hougaku(Player *self)
{
	return Camera_get_hougaku(self->camera);
}

int Player_get_time(Player *self)
{
	return self->time_limit / 60;
}

int Player_get_paper(Player *self)
{
	return self->get_paper;
}

void move_area(Player *self)
{
	int hougaku = Player_get_hougaku(self);

	if (hougaku == 0)
	{
		if(self->area == 0 && Room_get_door(self->room) ){ self->area++; }
		else if(self->area > 0 && self->area < 3 ){ self->area++; }
		else if(self->area > 5 && self->area < 8 ){ self->area--; }
	}
	else if (hougaku == 1)
	{
		if(self->area == 3 && Room_get_slide(self->room)){ self->area++; }
		else if(self->area > 3 && self->area < 5 ){ self->area++; }
	}
	else if (hougaku == 2)
	{
		if(self->area > 4 && self->area < 7 ){ self->area++; }
		else if(self->area > 1 && self->area < 4 ){ self->area--; }
		else if(self->area == 1 && Room_get_door(self->room)){ self->area--; }
	}
	else if (hougaku == 3)
	{
		if(self->area == 4 && Room_get_slide(self->room)){ self->area--; }
		else if(self->area > 4 && self->area < 6 ){ self->area--; }
	}

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

	if(self->area > 0){ Room_get_door(self->room) == false; }

	self->count++;

	if(self->time_limit > 0 || self->player_state == 0 ){ self->time_limit--;}
}

// �I������������
void Player_Finalize( Player *self )
{
    delete self;
}
