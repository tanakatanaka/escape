#include "DxLib.h"
#include "Camera.h"
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

	int test;
};

static const VECTOR cam_pos[8] =
{
	{2017,250,-310}, {882,250,-310}, {195,250,-310}, {-592,250,-310},
	{-592,250,255}, {-592,250,820}, {158,250,820}, {928,250,450}
};

static const VECTOR pt_pos[8] =
{
	{-920,200,-310}, {-920,200,-310}, {-920,200,-310}, {-592,250,-310},
	{-592,250,1020}, {-592,250,1020}, {-592,250,1020}, {-592,250,1020}
};

// ‰Šú‰»‚ğ‚·‚é
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
	self->muki = 0;
	self->test = 0;

	//–¶•`‰æon:‚É‚Â‚¢‚Äcolor‚ÅFEst`nI
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
			self->pt = pt_pos[self->area];
		}
	}
	
}



// “®‚«‚ğŒvZ‚·‚é
void Camera_Update( Camera *self )
{
	if(self->test == 1){SetCameraPositionAndTarget_UpVecY(self->cam, self->pt);}
	else if(self->test == 0){SetCameraPositionAndAngle( self->cam, 0.0f, self->HRotate, 0.0f ) ;}

	//•ûŠp‚É‚Â‚¢‚Ä
	if(self->swit == 0 && self->muki == 1){self->swit = 1;	self->muki = 0;}
	else if(self->swit == 0 && self->muki == 2){self->swit = 2; self->muki = 0;}
	
	role_cam(self);
	
	if(self->move_swit == 0 && self->area != self->old_a){self->move_swit = 1;}

	move_cam(self);

	if(Pad_Get(KEY_INPUT_V) == -1 )
	{
		if(self->test == 1){self->test = 0;}
		else if(self->test == 0){self->test = 1;}
	}

}

// •`‰æ‚·‚é
void Camera_Draw( Camera *self)
{
	DrawSphere3D( self->pt, 50, 32, GetColor( 0,255,127 ), GetColor( 0,255,127 ), TRUE ) ;

}

// I—¹ˆ—‚ğ‚·‚é
void Camera_Finalize( Camera *self )
{

}
