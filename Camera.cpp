#include "DxLib.h"
#include "Camera.h"
#include <math.h>
#include <stdio.h>
#include "pad.h"
#include "vector_operator.h"

#define ROTE 1.570796
#define MOVE_CUT 50

struct Camera 
{
	VECTOR pt;
	int count;
	int swit;
	int move_swit;
	int move_count;
	int area;
	int old_area;
	int muki;
	//視点関係の変数
	int camera_mode;
	float look_camera_pt;

};

static const VECTOR cam_pos[8] =
{
	{2017,250,-310}, {882,250,-310}, {195,250,-310}, {-592,250,-310},
	{-592,250,255}, {-592,250,820}, {158,250,820}, {928,250,450}
};

// 初期化をする
Camera *Camera_Initialize()
{
	Camera *self;
	self = (Camera *)malloc(sizeof(Camera));
	self->area = 0;
	self->old_area = 0;
	self->pt = VGet(0, -ROTE, 0);
	self->move_swit = 0;
	self->move_count = 0;
	self->swit = 0;
	self->count = 0;
	self->muki = 0;
	
	//視点関係の初期値
	self->camera_mode = 0;


	//霧描画on:についてcolorで色・st～始終
	SetFogEnable( TRUE );
	SetFogColor( 0,0,0 );
	SetFogStartEnd( 500,  1500) ;
	return self;
}

void Camera_get_area(Camera *self, int area)
{
	self->area = area;
}

void Camera_get_muki(Camera *self, int muki)
{
	self->muki = muki;
}

int Camera_get_muki(Camera *self)
{
	if (self->pt.y < ROTE / 2) { return 0; }
	else if (self->pt.y < ROTE * 3 / 2) { return 1; }
	else if (self->pt.y < ROTE * 5 / 2) { return 2; }
	else if (self->pt.y < ROTE * 7 / 2) { return 3; }
	return 0;
}

int Camera_get_camera_mode(Camera *self, int camera_mode)
{
	int role_count = 0;

	if(camera_mode % 2 == 1)
	{
		self->look_camera_pt = self->pt.y;
		self->pt.x = 0;
	}
	else
	{
		role_count = Camera_get_muki(self);
		self->pt.y = role_count * ROTE;
		self->pt.x = 0;
	}

	self->camera_mode = camera_mode;

	return role_count;
}

void Camera_get_pt(Camera *self, int type, float point)
{
	if(type == 0){self->pt.x += point;}
	else {self->pt.y += point;}
}

void role_cam(Camera *self)
{
	if(self->swit != 0)
	{
		int sign;
		int cut = 15;
		if(self->swit == 1){sign = 1;}
		else if(self->swit == 2){sign = -1;}

		if(self->count < cut)
		{
			self->pt.y += (float) (sign * ROTE / cut);
			self->count++;
		}
		else{self->count = 0; self->swit = 0;}

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
	if(self->camera_mode % 2 == 0)
	{
		//方角について
		if(self->swit == 0 && self->muki == 1){self->swit = 1;	self->muki = 0;}
		else if(self->swit == 0 && self->muki == 2){self->swit = 2; self->muki = 0;}
		role_cam(self);

		//移動スイッチについて
		if(self->move_swit == 0 && self->area != self->old_area){self->move_swit = 1;}
		move_cam(self);

		
	}
	


}

// 描画する
void Camera_Draw( Camera *self)
{
    const VECTOR &old = cam_pos[self->old_area];
    const VECTOR &next = cam_pos[self->area];
    VECTOR cam = old;
    
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
