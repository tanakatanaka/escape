#include "DxLib.h"
#include "Keyboard.h"
#include "Game.h"
#include "Room.h"


static const int NUM = 2;        //プレイヤーの数

struct Game
{
	Room *room;

};

// 初期化をする
Game *Game_Initialize()
{
	Game *self;
	int gazo = LoadGraph("画像/キャラクタ01.png");
	self = (Game *)malloc(sizeof(Game));
	self->room = Room_Initialize();

	return self;
}


// 動きを計算する
void Game_Update(Game *self)
{
	Keyboard_Update();    //キーボードの更新
	
	for( int i=0; i<NUM; i++ )
	{
        
    }
}

// 描画する
void Game_Draw(Game *self)
{
	 Room_Draw(self->room);
   
}

// 終了処理をする
void Game_Finalize(Game *self )
{
	for( int i=0; i<NUM; i++ )
	{
          
    }
	
}
