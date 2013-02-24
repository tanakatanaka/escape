#ifndef DEF_Room_H //二重include防止

#define DEF_Room_H

struct Room;

#include <string>
#include <vector>

// 初期化をする
Room *Room_Initialize();

void Room_act(Room *self, std::vector<std::string> &act);
void Room_set_are(Room *self, int area);
bool Room_get_door(Room *self);
bool Room_get_slide(Room *self);


// 動きを計算する
void Room_Update( Room *Room );

// 描画する
void Room_Draw( Room *Room );

// 終了処理をする
void Room_Finalize( Room *Room );

#endif