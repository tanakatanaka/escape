#include "DxLib.h"
#include "Keyboard.h"
#include "Camera.h"

struct Camera
{
	VECTOR cam;
}; 

// 初期化をする
Camera *Camera_Initialize()
{
	Camera *self;
	self = (Camera *)malloc(sizeof(Camera));
	return self;
}

// 動きを計算する
void Camera_Update( Camera *self )
{
    
}

// 描画する
void Camera_Draw( Camera *self){
   
}

// 終了処理をする
void Camera_Finalize( Camera *self )
{

}
