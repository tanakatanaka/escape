#ifndef DEF_Player_H //“ñdinclude–h~

#define DEF_Player_H

#include "Camera.h"
#include "Console.h"
#include "Room.h"
#include <string>
#include <vector>

struct Player
{
	Camera *camera;
	Console *console;
	Room *room;
    int area;
	int count;
	int time_limit;
	int get_paper;
};

// ‰Šú‰»‚ğ‚·‚é
Player *Player_Initialize(Camera *camera, Console *console, Room *room);

int Player_get_area(Player *self);
int Player_get_hougaku(Player *self);
int Player_get_time(Player *self);
int Player_get_paper(Player *self);


// “®‚«‚ğŒvZ‚·‚é
void Player_Update( Player *Player );

// •`‰æ‚·‚é
void Player_Draw( Player *Player );

// I—¹ˆ—‚ğ‚·‚é
void Player_Finalize( Player *Player );

#endif