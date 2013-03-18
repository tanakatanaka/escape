#ifndef DEF_Room_H //��dinclude�h�~

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


// ������������
Room *Room_Initialize();

void Room_set_area(Room *self, int area);
bool Room_get_door(Room *self);
bool Room_get_slide(Room *self);


// �������v�Z����
void Room_Update( Room *Room );

// �`�悷��
void Room_Draw( Room *Room );

// �I������������
void Room_Finalize( Room *Room );

#endif