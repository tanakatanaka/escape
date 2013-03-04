#ifndef DEF_Room_H //��dinclude�h�~

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
	int swit; //door�p
	int count;
	int s_swit; //glass�p
	int s_count;
	double slide;
	bool slide_lock;
	bool get_hammer;
	bool break_pot;
};


// ������������
Room *Room_Initialize();

void Room_act(Room *self, const char *act);
void Room_set_are(Room *self, int area);
bool Room_get_door(Room *self);
bool Room_get_slide(Room *self);


// �������v�Z����
void Room_Update( Room *Room );

// �`�悷��
void Room_Draw( Room *Room );

// �I������������
void Room_Finalize( Room *Room );

#endif