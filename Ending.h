#ifndef DEF_ENDING_H //��dinclude�h�~

#define DEF_ENDING_H

struct Ending;

// ������������
Ending *Ending_Initialize();

// �������v�Z����
void Ending_Update( Ending *Ending );

// �`�悷��
void Ending_Draw( Ending *Ending );

// �I������������
void Ending_Finalize( Ending *Ending );

#endif