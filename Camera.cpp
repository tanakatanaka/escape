#include "DxLib.h"
#include "Camera.h"
#include <math.h>
#include <stdio.h>
#include "pad.h"
#include "vector_operator.h"

#define ROTE 1.570796

struct Camera 
{
	VECTOR cam;
	VECTOR pt;
	float HRotate;
	int count;
	int swit;
	int move_swit;
	int move_count;
	int area;
	int old_a;
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
	self->old_a = 0;
	self->cam = cam_pos[0];
	self->pt = VGet(0,200,0); 
	self->HRotate = -1.570796f;
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

int Camera_look_to(Camera *self)
{
	int count = 1;

	if(self->pt.y > self->look_camera_pt + (ROTE * 0.5))
	{	
		while(1)
		{
			if(self->pt.y < self->look_camera_pt + (count * ROTE  + (ROTE * 0.5))){break;}
			count++;
		}
		self->HRotate += count * ROTE;
		
	}
	else if(self->pt.y < self->look_camera_pt - (ROTE * 0.5))
	{
		while(1)
		{
			if(self->pt.y > self->look_camera_pt - (count * ROTE  + (ROTE * 0.5))){break;}
			count++;
		}
		self->HRotate -= count * ROTE;
		count = -count;
	}
	else{count = 0;}

	return count;
}

int Camera_get_camera_mode(Camera *self, int camera_mode)
{
	int role_count = 0;

	if(camera_mode % 2 == 1)
	{
		self->look_camera_pt = self->HRotate;
		self->pt = VGet(0.0f, self->HRotate, 0.0f);
	}
	else{ role_count = Camera_look_to(self);}

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
			self->HRotate += (float) (sign * ROTE / cut);
			self->count++;
		}
		else{self->count = 0; self->swit = 0;}

	}
}

void move_cam(Camera *self)
{
	int cut = 50;
	const VECTOR &old = cam_pos[self->old_a];
	const VECTOR &next = cam_pos[self->area];

	self->cam = old + (next - old) * (self->move_count / (float)cut);
	self->move_count++;

	if (self->move_count == cut)
	{
		self->cam = next;
		self->move_count = 0;
		self->move_swit = 0;
		self->old_a = self->area;
	}
}

// 動きを計算する
void Camera_Update( Camera *self )
{
	if(self->camera_mode % 2 == 0)
	{
		SetCameraPositionAndAngle( self->cam, 0.0f, self->HRotate, 0.0f ) ;
		
		//方角について
		if(self->swit == 0 && self->muki == 1){self->swit = 1;	self->muki = 0;}
		else if(self->swit == 0 && self->muki == 2){self->swit = 2; self->muki = 0;}
		role_cam(self);

		//移動スイッチについて
		if(self->move_swit == 0 && self->area != self->old_a){self->move_swit = 1;}
		move_cam(self);

		
	}
	if(self->camera_mode % 2 == 1)
	{
		SetCameraPositionAndAngle( self->cam, self->pt.x, self->pt.y, 0.0f);
	}
	
	


}

// 描画する
void Camera_Draw( Camera *self)
{

}

// 終了処理をする
void Camera_Finalize( Camera *self )
{

}
