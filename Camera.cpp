#include "DxLib.h"
#include "Camera.h"
#include <math.h>
#include <stdio.h>
#include "pad.h"
#include "console.h"
#include "vector_operator.h"

#ifndef M_PI
#  define M_PI (atanf(1.0) * 4)
#endif

#define MOVE_CUT 50.0f
#define ROLE_CUT 15

/*
0: 前向き -X方向 270度
1: 右向き -Z方向 0度
2: 後向き +X方向 90度
3: 左向き +Z方向 180度
*/
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
	self->pt = VGet(0, 0, 0);
	self->move_swit = 0;
	self->move_count = 0;
	self->role_swit= 0;
	self->count = 0;
	self->muki = 0;
	
	//視点関係の初期値
	self->look_at = 0;

	return self;
}

void Camera_set_area(Camera *self, int area)
{
	self->area = area;
}

int Camera_get_hougaku(Camera *self)
{
	//play_cam 0:playerから　1:cameraから
	return ((int)(self->pt.y + 0.5f)) % 4;
}


int Camera_is_look_at(Camera *self)
{
	return self->look_at % 2;
}


void look_out_over(Camera *self)
{
	float move_point_x = 0.04f;
	float move_point_y = move_point_x / (M_PI / 2);

	if(CheckHitKey(KEY_INPUT_UP)){self->pt.x -= move_point_x;}
	else if(CheckHitKey(KEY_INPUT_DOWN)){self->pt.x += move_point_x;}

	if(CheckHitKey(KEY_INPUT_RIGHT)){self->pt.y += move_point_y;}
	else if(CheckHitKey(KEY_INPUT_LEFT)){self->pt.y -= move_point_y;}
}

void role_cam(Camera *self)
{
	if(self->count < ROLE_CUT)
	{
		self->pt.y += self->role_swit / (float)ROLE_CUT;
		self->count++;
	}
	else if (self->count == ROLE_CUT)
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
	if(Console_is_input(self->console) == 0)
	{
		if(self->look_at % 2 == 0)
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
		else
		{
			//カメラ操作状態
			look_out_over(self);
		}
	
		if (Pad_Get( KEY_INPUT_Z ) == -1)
		{
			self->look_at++;

			if (Camera_is_look_at(self) == 0)
			{ 
				self->pt.x = 0;
				self->pt.y = Camera_get_hougaku(self); 
			}
		}
	}

	if (self->pt.y < 0)
	{
		self->pt.y += 4;
	}
	else if (self->pt.y > 4)
	{
		self->pt.y -= 4;
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
    
	DrawFormatString( 540, 120, GetColor( 255, 255, 0 ), "%f", self->pt.y);
    SetCameraPositionAndAngle(cam, self->pt.x, (self->pt.y + 3) * M_PI / 2, 0.0f);
}

// 終了処理をする
void Camera_Finalize( Camera *self )
{

}
