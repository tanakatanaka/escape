#ifndef DEF_Twod_H //��dinclude�h�~

#define DEF_Twod_H

struct Twod;

// ������������
Twod *Twod_Initialize();

// �������v�Z����
void Twod_Update( Twod *Twod );

// �`�悷��
void Twod_Draw( Twod *Twod );

// �I������������
void Twod_Finalize( Twod *Twod );

#endif