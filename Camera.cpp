#include "DxLib.h"
#include "Keyboard.h"
#include "Camera.h"

struct Camera
{
	VECTOR cam;
}; 

// ‰Šú‰»‚ğ‚·‚é
Camera *Camera_Initialize()
{
	Camera *self;
	self = (Camera *)malloc(sizeof(Camera));
	return self;
}

// “®‚«‚ğŒvZ‚·‚é
void Camera_Update( Camera *self )
{
    
}

// •`‰æ‚·‚é
void Camera_Draw( Camera *self){
   
}

// I—¹ˆ—‚ğ‚·‚é
void Camera_Finalize( Camera *self )
{

}
