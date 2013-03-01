#include "DxLib.h"
#include "Room.h"
#include "Pad.h"
#include <string>
#include <vector>



#define OPEN 1.658064
#define SLIDE 505

struct Room
{
	int area;
    int room;
	int door;
	int glass;
	int hammer;
	int pot;
	double rotY;
	int swit; //door用
	int count;
	int s_swit; //glass用
	int s_count;
	double slide;
	bool slide_lock;
	bool get_hammer;
	bool break_pot;
}; 

// 初期化をする
Room *Room_Initialize()
{
	Room *self;
	self = (Room *)malloc(sizeof(Room));

	self->area = 0;

    self->room = MV1LoadModel("meta/room.mqo") ;    //model画像ハンドルの格納
	self->door = MV1LoadModel("meta/door.mqo") ;    //model画像ハンドルの格納
	self->glass = MV1LoadModel("meta/glass.mqo") ;    //model画像ハンドルの格納
	self->hammer = MV1LoadModel("meta/hammer.mqo") ;
	self->pot = MV1LoadModel("meta/pot.mqo") ;

	self->rotY = 0.0f;
	self->swit = 0;
	self->count = 0;
	self->s_swit = 0;
	self->s_count = 0;
	self->slide = 0;
	self->slide_lock = false;
	self->get_hammer = false;
	self->break_pot = false;

	return self;
}

void Room_act(Room *self, const char *action)
{
  std::string act(action);
  
	if(act == "open_door" && self->rotY != OPEN)
	{
		self->swit = 1;
	}
	
	if(act == "un_lock")
	{
		self->slide_lock = true;
	}

	if(self->slide_lock == true && act == "open_slide" && self->slide != SLIDE)
	{
		self->s_swit = 1;
	}

	if(act == "get_hammer")
	{
		self->get_hammer = true;
	}
  
	if(self->get_hammer == true && act == "break_pot")
	{
		self->break_pot = true;
	}
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

void Room_set_are(Room *self, int area)
{
	self->area = area;
}

// 動きを計算する
void Room_Update( Room *self )
{
	//開く
	if(self->swit == 1 || self->swit == -1){ door_open(self); }
	if( self->s_swit == 1 || self->s_swit == -1 ){ slide_glass(self); }

	// 閉じる
	if(self->area > 0 && self->rotY == OPEN) { self->swit = -1; }
}		

// 描画する
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
	if(!self->get_hammer){ MV1DrawModel(self->hammer); }
	if(!self->break_pot){ MV1DrawModel(self->pot); }
	MV1DrawModel(self->glass);
	
	
}

// 終了処理をする
void Room_Finalize( Room *self )
{
    
}
