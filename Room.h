#ifndef DEF_Room_H //二重include防止

#define DEF_Room_H

#include <string>
#include <vector>
#include "ModelID.h"

// TOLUA_BEGIN

struct Room
{
    ModelID room;
	int window;
	int coffee;
	ModelID door;
	ModelID glass;
	ModelID hammer;
	ModelID pot;
	ModelID table;
	int black_cap;
	int green_cap;
	int yellow_cap;
	ModelID bed;
	int makura;
	int huton;
	int stand;
	ModelID paper0;
	ModelID paper1;
	ModelID paper2;
	ModelID paper3;
	double rotY;
	int swit;
	int count;
	int s_swit;
	int s_count;
	int door_close_count;
	double slide;
	int role;
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