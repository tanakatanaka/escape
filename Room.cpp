#include "DxLib.h"
#include "Room.h"
#include "Player.h"
#include "Pad.h"
#include <string>
#include <vector>


#define OPEN 1.658064
#define SLIDE 505

struct Room
{
	Player *player;

    int room;
	int door;
	int glass;
	int hammer;
	int pot;
	
	double rotY;
	int swit; //door—p
	int count;
	int s_swit; //glass—p
	int s_count;
	double slide;
	bool slide_lock;
}; 

// ‰Šú‰»‚ğ‚·‚é
Room *Room_Initialize(Player *player)
{
	Room *self;
	self = (Room *)malloc(sizeof(Room));
	self->player = player;

    self->room = MV1LoadModel("meta/room.mqo") ;    //model‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[
	self->door = MV1LoadModel("meta/door.mqo") ;    //model‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[
	self->glass = MV1LoadModel("meta/glass.mqo") ;    //model‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[
	self->hammer = MV1LoadModel("meta/hammer.mqo") ;
	self->pot = MV1LoadModel("meta/pot.mqo") ;

	self->rotY = 0.0f;
	self->swit = 0;
	self->count = 0;
	self->s_swit = 0;
	self->s_count = 0;
	self->slide = 0;
	self->slide_lock = false;

	return self;
}

void Room_act(Room *self, std::vector<std::string> &act)
{
	if(act[1] == "open_door" && self->rotY != OPEN)
	{
			self->swit = 1;
	}
	
	if(act[1] == "un_lock")
	{
		self->slide_lock = true;
	}

	if(self->slide_lock == true && act[1] == "open_slide" && self->slide != SLIDE)
	{
		self->s_swit = 1;
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





// “®‚«‚ğŒvZ‚·‚é
void Room_Update( Room *self )
{
	//ŠJ‚­
	if(self->swit == 1 || self->swit == -1){ door_open(self); }
	if( self->s_swit == 1 || self->s_swit == -1 ){ slide_glass(self); }

	// •Â‚¶‚é
	if(Player_get_area(self->player) > 0 && self->rotY == OPEN) { self->swit = -1; }
}		

// •`‰æ‚·‚é
void Room_Draw( Room *self)
{
	MV1SetRotationXYZ( self->door, VGet( 0, self->rotY, 0 ) );

	MV1SetPosition(self->room, VGet( 200, 0, 300 ) );
	MV1SetPosition(self->door, VGet( 1250, 0, -540 ) );
	MV1SetPosition(self->glass, VGet( 200 + self->slide, 0, 300) );
	MV1SetPosition(self->hammer, VGet( 200, 0, 300 ) );
	MV1SetPosition(self->pot, VGet( 200, 0, 300 ) );

	MV1DrawModel(self->room);
	MV1DrawModel(self->door);
	MV1DrawModel(self->hammer);
	MV1DrawModel(self->pot);
	MV1DrawModel(self->glass);
	
	
}

// I—¹ˆ—‚ğ‚·‚é
void Room_Finalize( Room *self )
{
    
}
