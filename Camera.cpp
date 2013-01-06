#include "DxLib.h"
#include "Camera.h"
#include <stdio.h>
#include "pad.h"
#include "vector_operator.h"

#define ROTE 1.570796

struct Camera 
{
	int mode;
	VECTOR cam;
	VECTOR pt;
	float HRotate;
	int count;
	int swit;
	int move_swit;
	int move_count;
	int area;
	int old_a;
};

static const VECTOR cam_pos[8] =
{
	{1717,250,-310}, {982,250,-310}, {195,250,-310}, {-592,250,-310},
	{-592,250,255}, {-592,250,820}, {158,250,820}, {928,250,450}
};

static const VECTOR pt_pos[8] =
{
	{-920,200,-310}, {-920,200,-310}, {-920,200,-310}, {-592,250,-310},
	{-592,250,1020}, {-592,250,1020}, {-592,250,1020}, {-592,250,1020}
};

// 初期化をする
Camera *Camera_Initialize()
{
	Camera *self;
	self = (Camera *)malloc(sizeof(Camera));
	self->area = 0;
	self->old_a = 0;
	self->cam = cam_pos[0];
	self->pt = pt_pos[0];
	self->HRotate = -1.570796f;
	self->move_swit = 0;
	self->move_count = 0;
	self->swit = 0;
	self->count = 0;
	return self;
}

void Camera_get_area(Camera *self, int area)
{
	self->area = area;
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
	if(self->move_swit == 1)
	{
		int cut = 60;
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
	
}



// 動きを計算する
void Camera_Update( Camera *self )
{
	SetCameraPositionAndTarget_UpVecY(self->cam, self->pt);
	SetCameraPositionAndAngle( self->cam, 0.0f, self->HRotate, 0.0f ) ;

	//ルンバルンバルンバ
	if(self->swit == 0 && Pad_Get( KEY_INPUT_RIGHT ) == -1){self->swit = 1;	}
	else if(self->swit == 0 && Pad_Get(KEY_INPUT_LEFT ) == -1){self->swit = 2;}
	
	role_cam(self);
	
	if(self->move_swit == 0 && self->area != self->old_a){self->move_swit = 1;}

	move_cam(self);
	//self->cam = VGet(cam_pos[self->area][0],cam_pos[self->area][1],cam_pos[self->area][2]);


	if(Pad_Get(KEY_INPUT_X) == -1 )
	{
		self->mode++;
		printf("\narea = %d\n",self->area);
		if(self->mode %2 == 0){printf("\ncamre mode\n");}
		else{printf("\npoint mode\n");}
	}

}

// 描画する
void Camera_Draw( Camera *self)
{
	DrawSphere3D( self->pt, 50, 32, GetColor( 0,255,127 ), GetColor( 0,255,127 ), TRUE ) ;

}

// 終了処理をする
void Camera_Finalize( Camera *self )
{

}
