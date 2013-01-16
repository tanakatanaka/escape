#include "DxLib.h"
#include "Room.h"
#include "Pad.h"

#define OPEN 1.658064
#define SLIDE 505

struct Room
{
    int room;
	int door;
	int glass;
	double rotY;
	int swit; //door用
	int count;
	int s_swit; //glass用
	int s_count;
	double slide;
}; 

// 初期化をする
Room *Room_Initialize()
{
	Room *self;
	self = (Room *)malloc(sizeof(Room));
    self->room = MV1LoadModel("meta/room.mqo") ;    //model画像ハンドルの格納
	self->door = MV1LoadModel("meta/door.mqo") ;    //model画像ハンドルの格納
	self->glass = MV1LoadModel("meta/glass.mqo") ;    //model画像ハンドルの格納
	self->rotY = 0.0f;
	self->swit = 0;
	self->count = 0;
	self->s_swit = 0;
	self->s_count = 0;
	self->slide = 0;

	return self;
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
		printf("\nslide = %lf\n",self->slide);
	}
}



// 動きを計算する
void Room_Update( Room *self )
{
	/*
	if(CheckHitKey(KEY_INPUT_A)){self->rotY ++;}
	else if(CheckHitKey(KEY_INPUT_D)){self->rotY --;}
  */
	
	//door関連
	if(Pad_Get( KEY_INPUT_X ) == -1){ self->swit = 1;}
	else if(Pad_Get( KEY_INPUT_Z ) == -1){self->swit = -1;}

	if(self->swit == 1 || self->swit == -1){door_open(self);}
	MV1SetRotationXYZ( self->door, VGet( 0, self->rotY, 0 ) );

	//glass関連
	if(Pad_Get( KEY_INPUT_X ) == -1){ self->s_swit = 1;}
	else if(Pad_Get( KEY_INPUT_Z ) == -1){self->s_swit = -1;}

	if(self->swit == 1 || self->s_swit == -1){slide_glass(self);}

	

	MV1SetPosition(self->room, VGet( 200, 0, 300 ) );
	MV1SetPosition(self->door, VGet( 1250, 0, -540 ) );
	MV1SetPosition(self->glass, VGet( 200 + self->slide, 0, 300) );

	
    
}		

// 描画する
void Room_Draw( Room *self)
{
	MV1DrawModel(self->room);
	MV1DrawModel(self->door);
	MV1DrawModel(self->glass);
}

// 終了処理をする
void Room_Finalize( Room *self )
{
    
}
