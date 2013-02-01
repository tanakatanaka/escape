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

// 初期化をする
Player *Player_Initialize(Camera *camera, Console *console)
{
	Player *self;
	self = new Player();
	
	self->camera = camera;
	self->console = console;
	//player用
	self->hougaku = 0;
	self->area = 0;
	self->count = 30;

	return self;
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


// 動きを計算する
void Player_Update( Player *self )
{
	if(Console_is_input(self->console)  == 0)
	{
		//歩行もしくはカメラ操作状態
		if(Camera_is_look_at(self->camera) == 0)
		{
			//歩行状態
			if(Pad_Get( KEY_INPUT_RIGHT ) == -1)
			{
				Camera_set_muki(self->camera, 1);
				if(self->hougaku == 3){self->hougaku = 0;}
				else{self->hougaku++;}
			}
			else if(Pad_Get( KEY_INPUT_LEFT ) == -1)
			{
				Camera_set_muki(self->camera, 2);
				if(self->hougaku == 0){self->hougaku = 3;}
				else{self->hougaku--;}
			}
	
			if(self->count > 30 && Pad_Get( KEY_INPUT_UP ) == -1)
			{
				self->count = 0;
				move_area(self);
			}
		}
		else if(Camera_is_look_at(self->camera) == 1)
		{
			//カメラ操作状態
			float move_point = 0.04;

			if(CheckHitKey(KEY_INPUT_UP)){Camera_set_pt(self->camera, 0, -move_point);}
			else if(CheckHitKey(KEY_INPUT_DOWN)){Camera_set_pt(self->camera, 0, +move_point);}

			if(CheckHitKey(KEY_INPUT_RIGHT)){Camera_set_pt(self->camera, 1, move_point);}
			else if(CheckHitKey(KEY_INPUT_LEFT)){Camera_set_pt(self->camera, 1, -move_point);}

		}

		if(Pad_Get( KEY_INPUT_Z ) == -1)
		{
			self->hougaku = Camera_set_camera_mode(self->camera);
			printf("\n hougaku = %d \n", self->hougaku);
		}
	}

	//どんなモードでも
	if(Pad_Get(KEY_INPUT_ESCAPE) == 1)
	{ 

		if(Camera_is_look_at(self->camera) == 1)
		{

		}
	}
	self->count++;
}

// 描画する
void Player_Draw( Player *self)
{
    
}

// 終了処理をする
void Player_Finalize( Player *self )
{
    
}
