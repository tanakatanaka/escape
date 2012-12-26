#include "DxLib.h"
#include "Room.h"


struct Room
{
    int model;
	float rotY;
}; 

// 初期化をする
Room *Room_Initialize()
{
	Room *self;
	self = (Room *)malloc(sizeof(Room));
    self->model = MV1LoadModel("meta/room.mqo") ;    //画像ハンドルの格納
	
	self->rotY = 0.0f;
	return self;
}

// 動きを計算する
void Room_Update( Room *self )
{
		MV1SetPosition(self->model, VGet( 200.0f, 0.0f, 300.0f ) );
        MV1SetRotationXYZ( self->model, VGet( 0.0f, self->rotY, 0.0f ) );

		if(CheckHitKey(KEY_INPUT_A)){self->rotY -= (PHI / 180.0f);}
		else if(CheckHitKey(KEY_INPUT_D)){self->rotY += (PHI / 180.0f);}
}		

// 描画する
void Room_Draw( Room *self)
{
	MV1DrawModel( self->model);    
}

// 終了処理をする
void Room_Finalize( Room *self )
{
    
}
