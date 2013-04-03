#ifndef DEF_Room_H //��dinclude�h�~

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

// ������������
Room *Room_Initialize();

bool Room_get_door(Room *self);
bool Room_get_slide(Room *self);


// �������v�Z����
void Room_Update( Room *Room );

// �`�悷��
void Room_Draw( Room *Room );

// �I������������
void Room_Finalize( Room *Room );

#endif