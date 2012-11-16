#include "DxLib.h"
#include "Keyboard.h"
#include "Camera.h"
#include <stdio.h>


struct Camera
{
	VECTOR cam;
}; 

// ‰Šú‰»‚ğ‚·‚é
Camera *Camera_Initialize()
{
	Camera *self;
	self = (Camera *)malloc(sizeof(Camera));
	self->cam = VGet(0.0f,500.0f,-500.0f);
	return self;
}

// “®‚«‚ğŒvZ‚·‚é
void Camera_Update( Camera *self )
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
        SetCameraPositionAndTarget_UpVecY(self->cam,VGet(0.0f,0.0f,0.0f));

		if(1==CheckHitKey(KEY_INPUT_Z) )
		{
			printf("x %lf\n",self->cam.x);
			printf("y %lf\n",self->cam.y);
			printf("z %lf\n",self->cam.z);
			self->cam = VGet(0.0f,500.0f,-500.0f);
		}
}

// •`‰æ‚·‚é
void Camera_Draw( Camera *self){
   
}

// I—¹ˆ—‚ğ‚·‚é
void Camera_Finalize( Camera *self )
{

}
