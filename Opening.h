#ifndef DEF_Opening_H //��dinclude�h�~

#define DEF_Opening_H

struct Opening;

// ������������
Opening *Opening_Initialize();

//opening�̏�Ԃ�Ԃ�
int Opening_get_game_mode(Opening *self);

// �������v�Z����
void Opening_Update( Opening *Opening );

// �`�悷��
void Opening_Draw( Opening *Opening );

// �I������������
void Opening_Finalize( Opening *Opening );

#endif