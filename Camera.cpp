#include "DxLib.h"
#include "Camera.h"
#include <math.h>
#include <stdio.h>
#include "pad.h"
#include "vector_operator.h"

#define ROTE 1.570796
#define PI 3.1415926f

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
	double deg;
	double r;
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
	self->deg = 0; 
	self->r = 300;


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


double Camera_give_area(Camera *self)
{
	return self->deg;
}

void Camera_get_muki(Camera *self, int muki)
{
	self->muki = muki;
}

void Camera_get_camera_mode(Camera *self, int camera_mode, int hougaku)
{
	if(camera_mode % 2 == 1){self->deg = hougaku * 90;}
	self->camera_mode = camera_mode;
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
	if(self->move_swit = 1)
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
	
}

void look_out_cam(Camera *self)
{
	if(self->camera_mode % 2 == 1)
	{
		if(CheckHitKey(KEY_INPUT_UP)){self->pt.y += 10;}
		else if(CheckHitKey(KEY_INPUT_DOWN)){self->pt.y -= 10;}

		if(CheckHitKey(KEY_INPUT_RIGHT)){self->deg -= 5;}
		else if(CheckHitKey(KEY_INPUT_LEFT)){self->deg += 5;}
		
		if(CheckHitKey(KEY_INPUT_C)){self->r += 5;}
		else if(CheckHitKey(KEY_INPUT_X)){self->r -= 5;}
		
		self->pt.z = self->cam.z + self->r * sin(PI/180 * self->deg); 
		self->pt.x = self->cam.x + self->r * cos(PI/180 * self->deg); 
	}

}


// 動きを計算する
void Camera_Update( Camera *self )
{
	//if(self->camera_mode % 2 == 1){SetCameraPositionAndTarget_UpVecY(self->cam, self->pt);}
	if(self->camera_mode % 2 == 1){SetCameraPositionAndAngle( self->cam, self->pt.x, self->pt.y, self->pt.y );}
	else if(self->camera_mode % 2 == 0){SetCameraPositionAndAngle( self->cam, 0.0f, self->HRotate, 0.0f ) ;}

	//方角について
	if(self->swit == 0 && self->muki == 1){self->swit = 1;	self->muki = 0;}
	else if(self->swit == 0 && self->muki == 2){self->swit = 2; self->muki = 0;}
	
	role_cam(self);
	//移動スイッチについて
	if(self->move_swit == 0 && self->area != self->old_a){self->move_swit = 1;}

	move_cam(self);
	look_out_cam(self);

	if(Pad_Get(KEY_INPUT_F) == 1){printf("\ndeg = %lf\n",self->deg);}

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
