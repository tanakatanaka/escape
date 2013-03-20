#ifndef DEF_Room_H //二重include防止

#define DEF_Room_H

#include <string>
#include <vector>

// TOLUA_BEGIN

struct Room
{
    int room;
	int door;
	int glass;
	int hammer;
	int pot;
	int table;
	int black_cap;
	int green_cap;
	int yellow_cap;
	int paper0;
	int paper1;
	double rotY;
	int swit;
	int count;
	int s_swit;
	int s_count;
	double slide;
	int role;
	int x;
	int y;
};

// TOLUA_END

// 初期化をする
Room *Room_Initialize();

bool Room_get_door(Room *self);
bool Room_get_slide(Room *self);


// 動きを計算する
void Room_Update( Room *Room );

// 描画する
void Room_Draw( Room *Room );

// 終了処理をする
void Room_Finalize( Room *Room );

#endif