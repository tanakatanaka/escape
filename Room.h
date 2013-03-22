#ifndef DEF_Room_H //“ñdinclude–h~

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
	int bed;
	int makura;
	int huton;
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