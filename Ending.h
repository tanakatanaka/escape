#ifndef DEF_ENDING_H //��dinclude�h�~

#define DEF_ENDING_H

struct Ending;

#include "Player.h"

// ������������
Ending *Ending_Initialize(Player *player);

int Ending_get_next( Ending *self );

// �������v�Z����
void Ending_Update( Ending *Ending );

// �`�悷��
void Ending_Draw( Ending *Ending );

// �I������������
void Ending_Finalize( Ending *Ending );

#endif