#ifndef DEF_Player_H //二重include防止

#define DEF_Player_H

struct Player;

#include "Camera.h"
#include "Console.h"

// 初期化をする
Player *Player_Initialize(Camera *camera, Console *console);

//現在地を得る
void Player_set_area(Player *self, int area);
//方角を得る
void Player_set_hougaku(Player *self, int hougaku);

// 動きを計算する
void Player_Update( Player *Player );

// 描画する
void Player_Draw( Player *Player );

// 終了処理をする
void Player_Finalize( Player *Player );

#endif