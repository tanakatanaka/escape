#ifndef DEF_Twod_H //��dinclude�h�~

#define DEF_Twod_H

struct Twod;

#include "Player.h"

// ������������
Twod *Twod_Initialize(Player *player);
//�摜��`�惂�[�h�ɂ���
void Twod_add_image(Twod *self, int x, int y, int id);
//�摜������
void Twod_erase_image(Twod *self);
// �������v�Z����
void Twod_Update( Twod *Twod );
// �`�悷��
void Twod_Draw( Twod *Twod );
// �I������������
void Twod_Finalize( Twod *Twod );

#endif