#ifndef DEF_Room_H //二重include防止

#define DEF_Room_H

#include <string>
#include <vector>

struct Room
{
	int area;
    int room;
	int door;
	int glass;
	int hammer;
	int pot;
	int paper0;
	int paper1;
	double rotY;
	int swit;
	int count;
	int s_swit;
	int s_count;
	double slide;
	int role;
	bool get_hammer;
	bool break_pot;
	bool get_paper0;
	bool get_paper1;
	int x;
	int y;
};


// 初期化をする
Room *Room_Initialize();

void Room_set_area(Room *self, int area);
bool Room_get_door(Room *self);
bool Room_get_slide(Room *self);


// 動きを計算する
void Room_Update( Room *Room );

// 描画する
void Room_Draw( Room *Room );

// 終了処理をする
void Room_Finalize( Room *Room );

#endif