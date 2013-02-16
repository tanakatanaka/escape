#ifndef DEF_Room_H //��dinclude�h�~

#define DEF_Room_H

struct Room;

#include "Player.h"
#include <string>
#include <vector>

// ������������
Room *Room_Initialize(Player *player);

void Room_act(Room *self, std::vector<std::string> &act);

// �������v�Z����
void Room_Update( Room *Room );

// �`�悷��
void Room_Draw( Room *Room );

// �I������������
void Room_Finalize( Room *Room );

#endif