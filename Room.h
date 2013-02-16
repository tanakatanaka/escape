#ifndef DEF_Room_H //二重include防止

#define DEF_Room_H

struct Room;

#include "Player.h"
#include <string>
#include <vector>

// 初期化をする
Room *Room_Initialize(Player *player);

void Room_act(Room *self, std::vector<std::string> &act);

// 動きを計算する
void Room_Update( Room *Room );

// 描画する
void Room_Draw( Room *Room );

// 終了処理をする
void Room_Finalize( Room *Room );

#endif