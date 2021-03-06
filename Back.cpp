#include "DxLib.h"
#include "Pad.h"
#include "Back.h"
#include "Camera.h"
#include "ModelID.h"

struct Back
{
	ModelID sphere;
	Camera *camera;
}; 

// 初期化をする
Back *Back_Initialize( Camera *camera)
{
	Back *self;
	self = new Back();
	self->camera = camera;
	self->sphere = MV1LoadModel("meta/back/sphere.mqo") ;    //model画像ハンドルの格納
	MV1SetUseZBuffer(self->sphere, FALSE);
	MV1SetPosition(self->sphere, VGet( 0, 0, 0 ) );
	return self;
}


// 動きを計算する
void Back_Update( Back *self )
{
}

// 描画する
void Back_Draw( Back *self)
{
	Camera_Draw_back(self->camera);

	SetLightEnable(FALSE);
	SetFogEnable(FALSE);
	MV1DrawModel(self->sphere);
	
	SetLightEnable(TRUE);
    SetFogEnable(TRUE);
    SetFogColor(255, 255, 255);
    SetFogStartEnd(600,  1400) ;
}

// 終了処理をする
void Back_Finalize( Back *self )
{
	SetFogEnable(FALSE);
	delete self;
}
