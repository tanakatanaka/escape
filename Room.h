#ifndef DEF_Room_H //“ñdinclude–h~

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

// ‰Šú‰»‚ğ‚·‚é
Room *Room_Initialize();

bool Room_get_door(Room *self);
bool Room_get_slide(Room *self);


// “®‚«‚ğŒvZ‚·‚é
void Room_Update( Room *Room );

// •`‰æ‚·‚é
void Room_Draw( Room *Room );

// I—¹ˆ—‚ğ‚·‚é
void Room_Finalize( Room *Room );

#endif