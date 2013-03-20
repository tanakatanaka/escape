#ifndef DEF_Player_H //二重include防止

#define DEF_Player_H

#include "Camera.h"
#include "Console.h"
#include "Room.h"
#include <string>
#include <vector>

// TOLUA_BEGIN

struct Player
{
	Camera *camera;
	Console *console;
	Room *room;
    int area;
	int count;
	int time_limit;
	int get_paper;
	bool game_end;
};

// TOLUA_END

// 初期化をする
Player *Player_Initialize(Camera *camera, Console *console, Room *room);

// TOLUA_BEGIN
bool Player_get_end(Player *self);
int Player_get_area(Player *self);
int Player_get_hougaku(Player *self);
int Player_get_time(Player *self);
int Player_get_paper(Player *self);

// TOLUA_END

// 動きを計算する
void Player_Update( Player *Player );

// 描画する
void Player_Draw( Player *Player );

// 終了処理をする
void Player_Finalize( Player *Player );

#endif