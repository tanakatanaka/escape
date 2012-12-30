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
	int swit;
	int count;
};

float cam_pos [8][3] =
{
	{17,250,-310}, {-182,250,-310}, {-379,250,-310}, {-592,250,-310},
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
	self->mode= 0;
	self->cam = VGet(928,250,450);
	self->pt = VGet(-592,250,1020);
	self->HRotate = -1.570796;
	self->swit = 0;
	self->count  = 0;
	return self;
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
// 動きを計算する
void Camera_Update( Camera *self )
{
	SetCameraPositionAndTarget_UpVecY(self->cam, self->pt);
	SetCameraPositionAndAngle( self->cam, 0.0f, self->HRotate, 0.0f ) ;

	if(self->mode % 2 == 0)
	{
		if( 1==CheckHitKey(KEY_INPUT_LEFT) ) self->cam.x-=10;
			if( 1==CheckHitKey(KEY_INPUT_RIGHT) ) self->cam.x+=10;
			if( 1==CheckHitKey(KEY_INPUT_LSHIFT) || 1==CheckHitKey(KEY_INPUT_RSHIFT) ) {
				if( 1==CheckHitKey(KEY_INPUT_UP) ) self->cam.z+=10;
				if( 1==CheckHitKey(KEY_INPUT_DOWN) ) self->cam.z-=10;
			} else {
				if( 1==CheckHitKey(KEY_INPUT_UP) ) self->cam.y+=10;
				if( 1==CheckHitKey(KEY_INPUT_DOWN) ) self->cam.y-=10;
			}
			
	}
	else
	{
		if( 1==CheckHitKey(KEY_INPUT_LEFT) ) self->pt.x-=10;
			if( 1==CheckHitKey(KEY_INPUT_RIGHT) ) self->pt.x+=10;
			if( 1==CheckHitKey(KEY_INPUT_LSHIFT) || 1==CheckHitKey(KEY_INPUT_RSHIFT) ) {
				if( 1==CheckHitKey(KEY_INPUT_UP) ) self->pt.z+=10;
				if( 1==CheckHitKey(KEY_INPUT_DOWN) ) self->pt.z-=10;
			} else {
				if( 1==CheckHitKey(KEY_INPUT_UP) ) self->pt.y+=10;
				if( 1==CheckHitKey(KEY_INPUT_DOWN) ) self->pt.y-=10;
			}
	}

	//ルンバルンバルンバ
	if(self->swit == 0 && Pad_Get( KEY_INPUT_V ) == -1){self->swit = 1;	}
	else if(self->swit == 0 && Pad_Get( KEY_INPUT_C ) == -1){self->swit = 2;}

	role_cam(self);


	if(Pad_Get(KEY_INPUT_Z) == -1 )
	{
		printf("\ncam(x,y,z) = (%lf,%lf,%lf)\n",self->cam.x,self->cam.y,self->cam.z);
		printf("\npt(x,y,z) = (%lf,%lf,%lf)\n",self->pt.x,self->pt.y,self->pt.z);
		printf("\nhrote = %lf\n",self->HRotate);
	}
	
	if(Pad_Get(KEY_INPUT_X) == -1 )
	{
		self->mode++;
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
