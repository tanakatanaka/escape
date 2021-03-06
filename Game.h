#ifndef DEF_Game_H //二重include防止

#define DEF_Game_H

struct Game;

// 初期化をする
Game *Game_Initialize();

// 動きを計算する
bool Game_Update(Game *game );

// 描画する
void Game_Draw(Game *game );

// 終了処理をする
void Game_Finalize(Game *game );

#endif