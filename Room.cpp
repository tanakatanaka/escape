#include "DxLib.h"
#include "Room.h"
#include "Pad.h"
#include <string>
#include <vector>

#define PHI DX_PI_F
#define OPEN 1.658064
#define SLIDE 505

// ‰Šú‰»‚ð‚·‚é
Room *Room_Initialize()
{
	Room *self;
	self = new Room();

    self->room = MV1LoadModel("meta/room.mqo") ;    //model‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[
	self->window = MV1SearchFrame(self->room, "window");
	self->coffee = MV1SearchFrame(self->room, "coffee");
	self->door = MV1LoadModel("meta/door.mqo") ;    //model‰æ‘œƒnƒ“ƒhƒ‹‚ÌŠi”[
	self->glass = MV1LoadModel("meta/glass.mqo") ;  
	self->hammer = MV1LoadModel("meta/hammer.mqo") ;
	self->pot = MV1LoadModel("meta/pot.mqo") ;
	self->paper0 = MV1LoadModel("meta/paper.mqo") ;
	self->paper1 = MV1DuplicateModel(self->paper0) ;
	self->paper2 = MV1DuplicateModel(self->paper1) ;
	self->paper3 = MV1DuplicateModel(self->paper1) ;
	self->table = MV1LoadModel("meta/table.mqo") ;
	self->bed = MV1LoadModel("meta/bed.mqo") ;
	self->makura = MV1SearchFrame(self->bed, "makura");
	self->huton = MV1SearchFrame(self->bed, "huton");
	self->stand = MV1SearchFrame(self->bed, "cover");
	self->black_cap = MV1SearchFrame(self->table, "black_futa");
	self->yellow_cap = MV1SearchFrame(self->table, "yellow_futa");
	self->green_cap = MV1SearchFrame(self->table, "green_futa");
	

	self->door_close_count = 0;
	self->rotY = 0.0f;
	self->swit = 0;
	self->count = 0;
	self->s_swit = 0;
	self->s_count = 0;
	self->slide = 0;
	self->role = 0;

	return self;
}

bool Room_get_door(Room *self)
{
	if(self->rotY == OPEN)
	{
		return true;
	}

	return false;
}

bool Room_get_slide(Room *self)
{
	if(self->slide == SLIDE)
	{
		return true;
	}

	return false;
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

// “®‚«‚ðŒvŽZ‚·‚é
void Room_Update( Room *self )
{
	MV1SetRotationXYZ( self->door, VGet( 0, self->rotY, 0 ) );
	MV1SetPosition(self->room, VGet( 200, 0, 300 ) );
	MV1SetPosition(self->door, VGet( 1250, 0, -540 ) );
	MV1SetPosition(self->glass, VGet( 200 + self->slide, 0, 300) );
	MV1SetPosition(self->table, VGet( 200 - 43, 0, 300 + 721) );
	MV1SetPosition(self->bed, VGet( 200 + 668, 0, 300 + 632) );
	MV1SetPosition(self->hammer, VGet( 200, 0, 300 ) );
	MV1SetPosition(self->paper0,  VGet( 200 - 1206, 275, 300 - 59 ) );
	MV1SetPosition(self->pot, VGet( 200, 0, 300 ) ); 
	MV1SetRotationXYZ( self->paper1, VGet( 0, self->role * PHI / 360, 0 ) ); 
	MV1SetPosition(self->paper1, VGet( 200 - 746, 137, 300 + 741) );
	MV1SetRotationXYZ( self->paper2, VGet( 0, self->role * PHI / 360, 0 ) ); 
	MV1SetPosition(self->paper2, VGet( 200 + 528, 22 + 141, 300 + 724) );
	MV1SetRotationXYZ( self->paper3, VGet( 0, self->role * PHI / 360, 0 ) ); 
	MV1SetPosition(self->paper3, VGet( 200 + 726, 22 + 83, 300 + 582 ) );

	//ŠJ‚­
	if(self->swit == 1 || self->swit == -1){ door_open(self); }
	if( self->s_swit == 1 || self->s_swit == -1 ){ slide_glass(self); }

	self->role++;

	if(self->door_close_count > 0)
	{
		if(self->door_close_count == 1){self->swit = -1;}
		self->door_close_count--;
	}



	/*
	if(Pad_Get( KEY_INPUT_W ) > 0){ self->x++; }
	else if(Pad_Get( KEY_INPUT_S ) > 0){ self->x--; }

	if(Pad_Get( KEY_INPUT_D ) > 0){ self->y++; }
	else if(Pad_Get( KEY_INPUT_A ) > 0){ self->y--; }

	if(Pad_Get( KEY_INPUT_V ) > 0){ self->z++; }
	else if(Pad_Get( KEY_INPUT_B ) > 0){ self->z--; }
	*/

	//if(Pad_Get( KEY_INPUT_Q ) == -1){printf("\n x= %d y = %d  z = %d \n",self->x,self->y, self->z);}


}		

// •`‰æ‚·‚é
void Room_Draw( Room *self)
{
	MV1DrawModel(self->room);
	MV1DrawModel(self->door);
	MV1DrawModel(self->glass);
	MV1DrawModel(self->hammer); 
	MV1DrawModel(self->paper0);  
	MV1DrawModel(self->pot); 
	MV1DrawModel(self->paper1); 
	MV1DrawModel(self->table); 
	MV1DrawModel(self->bed); 
	MV1DrawModel(self->paper2);
	MV1DrawModel(self->paper3);

}

// I—¹ˆ—‚ð‚·‚é
void Room_Finalize( Room *self )
{
	MV1DeleteModel(self->room);
	MV1DeleteModel(self->door);
	MV1DeleteModel(self->glass);
	MV1DeleteModel(self->hammer); 
	MV1DeleteModel(self->paper0);  
	MV1DeleteModel(self->pot); 
	MV1DeleteModel(self->paper1); 
	MV1DeleteModel(self->table); 
	MV1DeleteModel(self->bed); 
	MV1DeleteModel(self->paper2);
	MV1DeleteModel(self->paper3);
	delete self;
}
