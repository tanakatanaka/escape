#include "DxLib.h"
#include "Pad.h"
#include "Camera.h"
#include "Console.h"
#include "Player.h"
#include "Room.h"
#include <string>
#include <vector>

struct Player
{
	Camera *camera;
	Console *console;
	Room *room;
    int area;
    int hougaku;
	int count;
	int time_limit;
}; 

// 初期化をする
Player *Player_Initialize(Camera *camera, Console *console, Room *room)
{
	Player *self;
	self = new Player();
	
	self->camera = camera;
	self->console = console;
	self->room = room;
	//player用
	self->hougaku = 0;
	self->area = 0;
	self->count = 30;
	self->time_limit = 18000;
	

	return self;
}

void Player_act(Player *self,  std::vector<std::string> &act)
{
	

	

}


int Player_get_area(Player *self)
{
	return self->area;
}

int Player_get_hougaku(Player *self)
{
	return Camera_get_hougaku(self->camera, 0);
}

int Player_get_time(Player *self)
{
	return self->time_limit / 60;
}

void move_area(Player *self)
{
	if(self->hougaku == 0)
	{
		if(self->area == 0 && Room_get_door(self->room) ){ self->area++; }
		else if(self->area > 0 && self->area < 3 ){ self->area++; }
		else if(self->area > 5 && self->area < 8 ){ self->area--; }
	}
	else if(self->hougaku == 1)
	{
		if(self->area == 3 && Room_get_slide(self->room)){ self->area++; }
		else if(self->area > 3 && self->area < 5 ){ self->area++; }
	}
	else if(self->hougaku == 2)
	{
		if(self->area > 4 && self->area < 7 ){ self->area++; }
		else if(self->area > 1 && self->area < 4 ){ self->area--; }
		else if(self->area == 1 && Room_get_door(self->room)){ self->area--; }
	}
	else if(self->hougaku == 3)
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

// 動きを計算する
void Player_Update( Player *self )
{
	if(Console_is_input(self->console)  == 0)
	{
		//歩行もしくはカメラ操作状態
		if(Camera_is_look_at(self->camera) == 0)
		{
			moving(self);//歩行状態 
		}
	}

	if(self->area > 0){ Room_get_door(self->room) == false; }

	Room_set_are(self->room, self->area);
	self->hougaku = Camera_get_hougaku(self->camera, 0);
	self->count++;
	self->time_limit--;
}

// 描画する
void Player_Draw( Player *self)
{
    
}

// 終了処理をする
void Player_Finalize( Player *self )
{
    
}
