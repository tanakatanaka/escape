#include "DxLib.h"
#include "Keyboard.h"
#include "Game.h"
#include "Player.h"

// 初期化をする
void Game_Initialize( Game_t *Game)
{
	
}

	


// 動きを計算する
void Game_Update( Game_t *Game )
{
	Keyboard_Update();    //キーボードの更新
    PlayerMgr_Update();    //プレイヤー管理モジュールの更新
}

// 描画する
void Game_Draw( Game_t Game )
{
    PlayerMgr_Draw();    //プレイヤー管理モジュールの描画
}

// 終了処理をする
void Game_Finalize( Game_t Game )
{
	PlayerMgr_Finalize();    //プレイヤー管理モジュールの終了処理   
}
