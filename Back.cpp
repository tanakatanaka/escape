#include "DxLib.h"
#include "Pad.h"
#include "Back.h"

struct Back
{
	int sphere;
}; 

// 初期化をする
Back *Back_Initialize( )
{
	Back *self;
	self = new Back();
	
	self->sphere = MV1LoadModel("meta/back/sphere.mqo") ;    //model画像ハンドルの格納

	return self;
}


// 動きを計算する
void Back_Update( Back *self )
{
	MV1SetPosition(self->sphere, VGet( 200, 0, 300 ) );
}

// 描画する
void Back_Draw( Back *self)
{
	MV1DrawModel(self->sphere);

}

// 終了処理をする
void Back_Finalize( Back *self )
{
	
}
