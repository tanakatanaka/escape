#include "DxLib.h"
#include "Keyboard.h"
#include "Game.h"
#include "Room.h"
#include "Camera.h"


static const int NUM = 2;        //プレイヤーの数

struct Game
{
	Room *room;
	Camera *camera;

};

// 初期化をする
Game *Game_Initialize()
{
	Game *self;
	int gazo = LoadGraph("画像/キャラクタ01.png");
	self = (Game *)malloc(sizeof(Game));
	self->camera = Camera_Initialize( );
	self->room = Room_Initialize();
	return self;
}


// 動きを計算する
void Game_Update(Game *self)
{
	Camera_Update(self->camera);
	Keyboard_Update();    //キーボードの更新
	Room_Update( self->room );
}

// 描画する
void Game_Draw(Game *self)
{
	 Room_Draw(self->room);
   
}

// 終了処理をする
void Game_Finalize(Game *self )
{
	
}
