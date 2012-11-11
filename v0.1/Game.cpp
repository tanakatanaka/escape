#include "DxLib.h"
#include "Keyboard.h"
#include "Game.h"
#include "PlayerMgr.h"

static const int NUM = 2;        //プレイヤーの数

struct Game
{
	Player *player[2];

};

// 初期化をする
Game Game_Initialize()
{
	Game *self;
	int gazo = LoadGraph("画像/キャラクタ01.png");
	self = (Game *)malloc(sizeof(Game));
	self->player[0] = Player_Initialize(10, gazo);
	self->player[1] = Player_Initialize(50, gazo);

	return *self;
}


// 動きを計算する
void Game_Update( Game *Game )
{
	Keyboard_Update();    //キーボードの更新
	
	for( int i=0; i<NUM; i++ )
	{
        Player_Update(self->player[NUM]);//更新
    }
}

// 描画する
void Game_Draw( Game Game )
{
	for( int i=0; i<NUM; i++ )
	{
         PlayerMgr_Draw(self->player[NUM]);    //プレイヤー管理モジュールの描画
    }
   
}

// 終了処理をする
void Game_Finalize( Game Game )
{
	for( int i=0; i<NUM; i++ )
	{
         PlayerMgr_Finalize(self->player[NUM]);    //プレイヤー管理モジュールの終了処理   
    }
	
}
