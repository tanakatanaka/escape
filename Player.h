#ifndef DEF_Player_H //��dinclude�h�~

#define DEF_Player_H

#include "Camera.h"
#include "Console.h"
#include "Room.h"
#include "Sound.h"
#include <string>
#include <vector>

// TOLUA_BEGIN

struct Player
{
	Camera *camera;
	Console *console;
	Room *room;
	Sound *sound;
    int area;
	int count;
	int time_limit;
	int get_paper;
	int p_state;
	bool out_window;
	bool drink_coffee;
	bool break_max;
};

// TOLUA_END

// ������������
Player *Player_Initialize(Camera *camera, Console *console, Room *room, Sound *sound);

// TOLUA_BEGIN
bool Player_get_achievement(Player *self, const char *name);
int Player_get_state(Player *self);
int Player_get_area(Player *self);
int Player_get_hougaku(Player *self);
int Player_get_time(Player *self);
int Player_get_paper(Player *self);

// TOLUA_END

// �������v�Z����
void Player_Update( Player *Player );

// �I������������
void Player_Finalize( Player *Player );

#endif