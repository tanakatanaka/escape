#ifndef DEF_Opening_H //二重include防止

#define DEF_Opening_H

struct Opening;

#include "Sound.h"

// 初期化をする
Opening *Opening_Initialize(Sound *sound);

//openingの状態を返す
int Opening_get_game_mode(Opening *self);

// 動きを計算する
void Opening_Update( Opening *Opening );

// 描画する
void Opening_Draw( Opening *Opening );

// 終了処理をする
void Opening_Finalize( Opening *Opening );

#endif