#include "DxLib.h"
#include "Keyboard.h"
#include "Room.h"

struct Room
{
    int model;
}; 

// 初期化をする
Room *Room_Initialize()
{
	Room *self;
	self = (Room *)malloc(sizeof(Room));
    self->model = MV1LoadModel("room.mqo") ;    //画像ハンドルの格納
	MV1SetPosition(self->model, VGet( 320.0f, -300.0f, 600.0f ) ) ;
	return self;
}

// 動きを計算する
void Room_Update( Room *self )
{
    if( Keyboard_Get( KEY_INPUT_UP   ) > 0 )
	{//上が押されていたら
       
    }
    if( Keyboard_Get( KEY_INPUT_DOWN ) > 0 )
	{//下が押されていたら
        
    }
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
