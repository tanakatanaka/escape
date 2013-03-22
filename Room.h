#ifndef DEF_Room_H //��dinclude�h�~

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