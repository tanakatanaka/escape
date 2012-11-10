#ifndef DEF_PLAYERMGR_H //二重include防止

#define DEF_PLAYERMGR_H

// 初期化をする
void PlayerMgr_Initialize();

// 動きを計算する
void PlayerMgr_Update();

// 描画する
void PlayerMgr_Draw();

// 終了処理をする
void PlayerMgr_Finalize();

#endif