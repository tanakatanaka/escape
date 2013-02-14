#ifndef DEF_Player_H //二重include防止

#define DEF_Player_H

struct Player;

#include "Camera.h"
#include "Console.h"
#include <string>

// 初期化をする
Player *Player_Initialize(Camera *camera, Console *console);

void Player_set_status(Player *self, std::string type, int plus, bool on_off);
int Player_get_area(Player *self);
int Player_get_hougaku(Player *self);


// 動きを計算する
void Player_Update( Player *Player );

// 描画する
void Player_Draw( Player *Player );

// 終了処理をする
void Player_Finalize( Player *Player );

#endif