#include "DxLib.h"
#include "Camera.h"
#include <stdio.h>
#include "pad.h"

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

float cam_pos [8][3] =
{
	{1717,250,-310}, {982,250,-310}, {195,250,-310}, {-592,250,-310},
	{-592,250,255}, {-592,250,820}, {158,250,820}, {928,250,450}
};

float pt_pos [8][3] =
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
	self->cam = VGet(cam_pos[self->area][0],cam_pos[self->area][1],cam_pos[self->area][2]);
	self->pt = VGet(pt_pos [0][0],pt_pos [0][1],pt_pos [0][2]);
	self->HRotate = -1.570796;
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

		if(self->count < cut){self->HRotate += sign * ROTE /cut;self->count++;}
		else{self->count = 0; self->swit = 0;}

	}
}

void move_cam(Camera *self)
{
	if(self->move_swit == 1)
	{
		float cut = 10;
		VECTOR diff;
		
		diff.x = cam_pos[self->area][0] - cam_pos[self->old_a][0]; 
		

		self->cam = VGet(cam_pos[self->old_a][0] + float (diff[0] / cut),cam_pos[self->old_a][1] + float (diff[1] / cut),cam_pos[self->old_a][2] + float(diff[2] / cut));
		self->move_count++;

		if(self->move_count == cut )
		{
			self->cam = VGet(cam_pos[self->area][0],cam_pos[self->area][1],cam_pos[self->area][2]);
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
