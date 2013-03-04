#include "DxLib.h"
#include "Camera.h"
#include <math.h>
#include <stdio.h>
#include "pad.h"
#include "console.h"
#include "vector_operator.h"

#define ROTE 1.570796
#define MOVE_CUT 50

struct Camera 
{
	Console *console;
	VECTOR pt;
	int count;
	int role_swit;
	int move_swit;
	int move_count;
	int area;
	int old_area;
	int muki;

	//視点関係の変数
	int look_at;
	int zero_one;
};

static const VECTOR cam_pos[8] =
{
	{2017,250,-310}, {882,250,-310}, {195,250,-310}, {-592,250,-310},
	{-592,250,255}, {-592,250,820}, {158,250,820}, {928,250,450}
};

// 初期化をする
Camera *Camera_Initialize(Console *console)
{
	Camera *self;
	self = new Camera();
	self->console = console;

	self->area = 0;
	self->old_area = 0;
	self->pt = VGet(0, -ROTE, 0);
	self->move_swit = 0;
	self->move_count = 0;
	self->role_swit= 0;
	self->count = 0;
	self->muki = 0;
	
	//視点関係の初期値
	self->look_at = 0;
	self->zero_one = 0;

	return self;
}

void Camera_set_area(Camera *self, int area)
{
	self->area = area;
}

int Camera_get_hougaku(Camera *self, int play_cam)
{
	//play_cam 0:playerから　1:cameraから

	float y = fmodf(self->pt.y, ROTE * 4);
	int back = 3;

	if (y < 0)
	{
		y += ROTE * 4;
	}
  
	if (y < ROTE / 2) { back = 0; }
	else if (y < ROTE * 3 / 2) { back = 1; }
	else if (y < ROTE * 5 / 2) { back = 2; }
	else if (y < ROTE * 7 / 2) { back = 3; }

	if(play_cam == 0)
	{
		back++;
		if(back == 4){back = 0;}
	}

	return back;
}


int Camera_is_look_at(Camera *self)
{
	return self->look_at % 2;
}


void look_out_over(Camera *self)
{
	float move_point = 0.04;

	if(CheckHitKey(KEY_INPUT_UP)){self->pt.x -= move_point;}
	else if(CheckHitKey(KEY_INPUT_DOWN)){self->pt.x += move_point;}

	if(CheckHitKey(KEY_INPUT_RIGHT)){self->pt.y +=move_point;}
	else if(CheckHitKey(KEY_INPUT_LEFT)){self->pt.y -=move_point;}
}

void role_cam(Camera *self)
{
	int cut = 15;

	if(self->count < cut)
	{
		self->pt.y += (float) (self->role_swit * ROTE / cut);
		self->count++;
	}
	else
	{
		self->count = 0; 
		self->role_swit = 0;
	}
}

void move_cam(Camera *self)
{
	self->move_count++;

	if (self->move_count == MOVE_CUT)
	{
		self->move_count = 0;
		self->move_swit = 0;
		self->old_area = self->area;
	}
}

// 動きを計算する
void Camera_Update( Camera *self )
{
	if(self->look_at % 2 == 0 && Console_is_input(self->console) == 0)
	{
		if(self->role_swit == 0)
		{
			if(Pad_Get( KEY_INPUT_RIGHT ) == -1){ self->role_swit = 1; }
			else if(Pad_Get( KEY_INPUT_LEFT ) == -1){ self->role_swit = -1; }
		}
		else { role_cam(self); }


		//移動スイッチについて
		if(self->move_swit == 0 && self->area != self->old_area){self->move_swit = 1;}
		move_cam(self);
	}
	else if(self->look_at % 2 == 1)
	{
		//カメラ操作状態
		look_out_over(self);
	}

	if(Console_is_input(self->console) == 0 && Pad_Get( KEY_INPUT_Z ) == -1)
	{
		self->look_at++;
		int new_zero_one = Camera_is_look_at(self);

		if(self->zero_one == 1 && new_zero_one == 0)
		{ 
			self->pt.y = Camera_get_hougaku(self, 1) * ROTE;
			self->pt.x = 0;
		}
		self->zero_one = new_zero_one;
	}

}

// 描画する
void Camera_Draw( Camera *self)
{
    const VECTOR &old = cam_pos[self->old_area];
    const VECTOR &next = cam_pos[self->area];
    VECTOR cam = old;

	//霧描画on:についてcolorで色・st～始終
	SetFogEnable( TRUE );
	SetFogColor( 0,0,0 );
	SetFogStartEnd( 500,  1500) ;
    
    if (self->move_count < MOVE_CUT)
    {
       cam += (next - old) * (self->move_count / (float)MOVE_CUT);
    }
    
    SetCameraPositionAndAngle(cam, self->pt.x, self->pt.y, 0.0f);
}

// 終了処理をする
void Camera_Finalize( Camera *self )
{

}
