#ifndef DEF_Mess_H //��dinclude�h�~

#define DEF_Mess_H

struct Mess;

// ������������
Mess *Mess_Initialize();
//���t��ǉ�
void Mess_add_word(Mess *self,int x, int y, const char *word);
//���t����������
void Mess_erase_word(Mess *self);

// �������v�Z����
void Mess_Update( Mess *Mess );

// �`�悷��
void Mess_Draw( Mess *Mess );

// �I������������
void Mess_Finalize( Mess *Mess );

#endif