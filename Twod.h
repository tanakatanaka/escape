#ifndef DEF_Twod_H //二重include防止

#define DEF_Twod_H

struct Twod;

#include "Player.h"

// 初期化をする
Twod *Twod_Initialize(Player *player);
//画像を描画モードにする
void Twod_add_image(Twod *self, int x, int y, const char *name);
//画像を消す
void Twod_erase_image(Twod *self);
// 動きを計算する
void Twod_Update( Twod *Twod );
// 描画する
void Twod_Draw( Twod *Twod );
// 終了処理をする
void Twod_Finalize( Twod *Twod );

#endif