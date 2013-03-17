#include "DxLib.h"
#include "Room.h"
#include "Pad.h"
#include <string>
#include <vector>

#define OPEN 1.658064
#define SLIDE 505
 
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
	self->paper0 = MV1LoadModel("meta/paper0.mqo") ;
	self->paper1 = MV1LoadModel("meta/paper.mqo") ;
	
	self->rotY = 0.0f;
	self->swit = 0;
	self->count = 0;
	self->s_swit = 0;
	self->s_count = 0;
	self->slide = 0;
	self->slide_lock = false;
	self->get_hammer = false;
	self->break_pot = false;
	self->get_paper0 = false;
	self->get_paper1 = false;
	self->x = 0;
	self->y = 0;
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

void Room_set_are(Room *self, int area)
{
	self->area = area;
}

// 動きを計算する
void Room_Update( Room *self )
{
	MV1SetRotationXYZ( self->door, VGet( 0, self->rotY, 0 ) );
	MV1SetPosition(self->room, VGet( 200, 0, 300 ) );
	MV1SetPosition(self->door, VGet( 1250, 0, -540 ) );
	MV1SetPosition(self->glass, VGet( 200 + self->slide, 0, 300) );

	//開く
	if(self->swit == 1 || self->swit == -1){ door_open(self); }
	if( self->s_swit == 1 || self->s_swit == -1 ){ slide_glass(self); }
	// 閉じる
	if(self->area > 0 && self->rotY == OPEN) { self->swit = -1; }
	
	if(!self->get_hammer)
	{
		MV1SetPosition(self->hammer, VGet( 200, 0, 300 ) );
	}

	if(!self->get_paper0)
	{
		MV1SetPosition(self->paper0,  VGet( 200, 0, 300 ) );
	}

	if(!self->break_pot)
	{
		MV1SetPosition(self->pot, VGet( 200, 0, 300 ) ); 
	}
	else if(self->break_pot && !self->get_paper1)
	{
		MV1SetRotationXYZ( self->paper1, VGet( 0, self->role * PHI / 360, 0 ) ); 
		MV1SetPosition(self->paper1, VGet( 200 - 757, 22, 300 + 747) );
	}

	self->role++;




	/* デバッグ用操作
	if(Pad_Get( KEY_INPUT_W ) > 0){ self->x++; }
	else if(Pad_Get( KEY_INPUT_S ) > 0){ self->x--; }

	if(Pad_Get( KEY_INPUT_D ) > 0){ self->y++; }
	else if(Pad_Get( KEY_INPUT_A ) > 0){ self->y--; }

	if(Pad_Get( KEY_INPUT_Q ) == -1){printf("\n x= %d y = %d \n",self->x,self->y);}
	*/

}		

// 描画する
void Room_Draw( Room *self)
{
	MV1DrawModel(self->room);
	MV1DrawModel(self->door);
	MV1DrawModel(self->glass);

	if(!self->get_hammer)
	{
		MV1SetPosition(self->hammer, VGet( 200, 0, 300 ) );
		MV1DrawModel(self->hammer); 
	}

	if(!self->get_paper0)
	{
		MV1SetPosition(self->paper0,  VGet( 200, 0, 300 ) );
		MV1DrawModel(self->paper0);  
	}

	if(!self->break_pot)
	{
		MV1SetPosition(self->pot, VGet( 200, 0, 300 ) );
		MV1DrawModel(self->pot); 
	}
	else if(self->break_pot && !self->get_paper1)
	{
		MV1DrawModel(self->paper1); 
	}

	
	
}

// 終了処理をする
void Room_Finalize( Room *self )
{
    
}
