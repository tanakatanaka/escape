#include "DxLib.h"
#include "Camera.h"
#include <stdio.h>
#include "pad.h"

struct Camera
{
	int mode;
	VECTOR cam;
	VECTOR pt;
}; 

// 初期化をする
Camera *Camera_Initialize()
{
	Camera *self;
	self = (Camera *)malloc(sizeof(Camera));
	//self->cam = VGet(0.0f,500.0f,-500.0f);
	self->mode= 0;
	self->cam = VGet(1160,150,-130);
	self->pt = VGet(-920,190,-120);
	return self;
}

// 動きを計算する
void Camera_Update( Camera *self )
{
	SetCameraPositionAndTarget_UpVecY(self->cam, self->pt);

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
	if(Pad_Get( KEY_INPUT_RIGHT ) == -1)
	{
		
	}
	else if(Pad_Get( KEY_INPUT_LEFT ) == -1)
	{

	}




	if(Pad_Get(KEY_INPUT_Z) == -1 )
	{
		printf("\ncam(x,y,z) = (%lf,%lf,%lf)\n",self->cam.x,self->cam.y,self->cam.z);
		printf("\npt(x,y,z) = (%lf,%lf,%lf)\n",self->pt.x,self->pt.y,self->pt.z);
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
