#ifndef DEF_ENDING_H //二重include防止

#define DEF_ENDING_H

struct Ending;

#include "Player.h"
#include "Sound.h"

// 初期化をする
Ending *Ending_Initialize(Player *player, Sound *sound);

int Ending_get_next( Ending *self );

// 動きを計算する
void Ending_Update( Ending *Ending );

// 描画する
void Ending_Draw( Ending *Ending );

// 終了処理をする
void Ending_Finalize( Ending *Ending );

#endif