#include "DxLib.h"
#include "Room.h"


struct Room
{
    int room;
	int test;
	double rotY;
}; 

// 初期化をする
Room *Room_Initialize()
{
	Room *self;
	self = (Room *)malloc(sizeof(Room));
    self->room = MV1LoadModel("meta/room.mqo") ;    //画像ハンドルの格納
	self->test = MV1LoadModel("meta/test.mqo") ; 
	
	self->rotY = 0.0f;
	return self;
}

// 動きを計算する
void Room_Update( Room *self )
{
	//霧描画on:についてcolorで色
	SetFogEnable( TRUE );
	SetFogColor( 0, 0, 0 );


	MV1SetPosition(self->room, VGet( 200.0f, 0.0f, 300.0f ) );
    MV1SetRotationXYZ( self->room, VGet( 0.0f, self->rotY, 0.0f ) );

	MV1SetPosition(self->test, VGet( 0, 0, 0 ) );
    MV1SetRotationXYZ( self->test, VGet( 0, self->rotY, 0 ) );

	if(CheckHitKey(KEY_INPUT_A)){self->rotY -= (PHI / 180.0f);}
	else if(CheckHitKey(KEY_INPUT_D)){self->rotY += (PHI / 180.0f);}
}		

// 描画する
void Room_Draw( Room *self)
{
	MV1DrawModel( self->room);    
	MV1DrawModel( self->test); 
}

// 終了処理をする
void Room_Finalize( Room *self )
{
    
}
