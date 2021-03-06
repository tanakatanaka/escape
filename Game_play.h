#ifndef DEF_Game_play_H //二重include防止

#define DEF_Game_play_H

struct Game_play;

#include "Player.h"
#include "Sound.h"

// 初期化をする
Game_play *Game_play_Initialize(Sound *sound);

//Game_play終了条件を得る
Player *Game_play_get_result(Game_play *game_play);

// 動きを計算する
void Game_play_Update(Game_play *game_play );

// 描画する
void Game_play_Draw(Game_play *game_play );

// 終了処理をする
void Game_play_Finalize(Game_play *game_play );

#endif