#ifndef DEF_Back_H //��dinclude�h�~

#define DEF_Back_H

struct Back;


// ������������
Back *Back_Initialize();

// �������v�Z����
void Back_Update( Back *Back );

// �`�悷��
void Back_Draw( Back *Back );

// �I������������
void Back_Finalize( Back *Back );

#endif