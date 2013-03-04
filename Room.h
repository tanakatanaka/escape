#ifndef DEF_Room_H //“ñdinclude–h~

#define DEF_Room_H

struct Room;

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
	double rotY;
	int swit; //door—p
	int count;
	int s_swit; //glass—p
	int s_count;
	double slide;
	bool slide_lock;
	bool get_hammer;
	bool break_pot;
};


// ‰Šú‰»‚ğ‚·‚é
Room *Room_Initialize();

void Room_act(Room *self, const char *act);
void Room_set_are(Room *self, int area);
bool Room_get_door(Room *self);
bool Room_get_slide(Room *self);


// “®‚«‚ğŒvZ‚·‚é
void Room_Update( Room *Room );

// •`‰æ‚·‚é
void Room_Draw( Room *Room );

// I—¹ˆ—‚ğ‚·‚é
void Room_Finalize( Room *Room );

#endif