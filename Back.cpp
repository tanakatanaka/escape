#include "DxLib.h"
#include "Pad.h"
#include "Back.h"
#include "Camera.h"

struct Back
{
	int sphere;
	Camera *camera;
}; 

// 初期化をする
Back *Back_Initialize( Camera *camera)
{
	Back *self;
	self = new Back();
	self->camera = camera;
	self->sphere = MV1LoadModel("meta/back/sphere.mqo") ;    //model画像ハンドルの格納

	return self;
}


// 動きを計算する
void Back_Update( Back *self )
{
	VECTOR pt = Camera_get_angle(self->camera);

	SetCameraPositionAndTarget_UpVecY(VGet( 0.0f, 0.0f, 0.0f ),pt);
	MV1SetPosition(self->sphere, VGet( 200, 0, 300 ) );
}

// 描画する
void Back_Draw( Back *self)
{
	SetFogEnable(FALSE);
	MV1DrawModel(self->sphere);
	
	//霧描画on:についてcolorで色・st～始終
    SetFogEnable(TRUE);
    SetFogColor(0, 0, 0);
    SetFogStartEnd(500,  1500) ;
}

// 終了処理をする
void Back_Finalize( Back *self )
{
	SetFogEnable(FALSE);
}
