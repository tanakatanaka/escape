#ifndef DEF_Player_H //��dinclude�h�~

#define DEF_Player_H

struct Player;

#include "Camera.h"
#include "Console.h"
#include <string>
#include <vector>


// ������������
Player *Player_Initialize(Camera *camera, Console *console);

void Player_act(Player *self,  std::vector<std::string> &act);
int Player_get_area(Player *self);
int Player_get_hougaku(Player *self);
int Player_get_time(Player *self);


// �������v�Z����
void Player_Update( Player *Player );

// �`�悷��
void Player_Draw( Player *Player );

// �I������������
void Player_Finalize( Player *Player );

#endif