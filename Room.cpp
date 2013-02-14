#include "DxLib.h"
#include "Room.h"
#include "Player.h"
#include "Pad.h"

#define OPEN 1.658064
#define SLIDE 505

struct Room
{
	Player *player;

    int room;
	int door;
	int glass;
	double rotY;
	int swit; //door�p
	int count;
	int s_swit; //glass�p
	int s_count;
	double slide;
}; 

// ������������
Room *Room_Initialize(Player *player)
{
	Room *self;
	self = (Room *)malloc(sizeof(Room));
	self->player = player;

    self->room = MV1LoadModel("meta/room.mqo") ;    //model�摜�n���h���̊i�[
	self->door = MV1LoadModel("meta/door.mqo") ;    //model�摜�n���h���̊i�[
	self->glass = MV1LoadModel("meta/glass.mqo") ;    //model�摜�n���h���̊i�[
	self->rotY = 0.0f;
	self->swit = 0;
	self->count = 0;
	self->s_swit = 0;
	self->s_count = 0;
	self->slide = 0;

	return self;
}

void Room_set_door(Room *self)
{
	if(self->rotY != OPEN)
	{
		self->swit = 1;
	}
}

void door_open(Room *self)
{
	int cut = 15;
	if(self->count == cut)
	{ 
		if(self->swit == 1){self->rotY = OPEN;}
		else if(self->swit == -1){self->rotY = 0;}
		self->count = 0;
		self->swit = 0;
	}
	else
	{
		self->rotY += self->swit * OPEN / (float)cut;
		self->count++;
	}
}

void slide_glass(Room *self)
{
	int cut = 15;
	if(self->s_count == cut)
	{ 
		if(self->s_swit == 1){self->slide = SLIDE;}
		else if(self->s_swit == -1){self->slide = 0;}
		self->s_count = 0;
		self->s_swit = 0;
	}
	else
	{
		self->slide += self->s_swit * SLIDE / (float)cut;
		self->s_count++;
	}
}



// �������v�Z����
void Room_Update( Room *self )
{
	if(Player_get_area(self->player) > 0 && self->rotY == OPEN) 
	{ 
		self->swit = -1;
		Player_set_status(self->player, "open_door", 0, false);
	}

	if(self->swit == 1 || self->swit == -1){ door_open(self); }

	//glass�֘A
	if(Pad_Get( KEY_INPUT_X ) == -1){ self->s_swit = 1;}
	else if(Pad_Get( KEY_INPUT_Z ) == -1){self->s_swit = -1;}

	if(self->s_swit == 1 || self->s_swit == -1){slide_glass(self);}
}		

// �`�悷��
void Room_Draw( Room *self)
{
	MV1SetRotationXYZ( self->door, VGet( 0, self->rotY, 0 ) );

	MV1SetPosition(self->room, VGet( 200, 0, 300 ) );
	MV1SetPosition(self->door, VGet( 1250, 0, -540 ) );
	MV1SetPosition(self->glass, VGet( 200 + self->slide, 0, 300) );

	MV1DrawModel(self->room);
	MV1DrawModel(self->door);
	MV1DrawModel(self->glass);
}

// �I������������
void Room_Finalize( Room *self )
{
    
}
