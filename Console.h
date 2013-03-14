#ifndef DEF_Console_H //��dinclude�h�~

#define DEF_Console_H

struct Console;

#include "Sound.h"

// ������������
Console *Console_Initialize( Sound *sound);

//���̓��[�h�����s���[�h����Ԃ�
int Console_is_input(Console *self);
//�R���\�[���̕�����Ԃ��֐�
const char *console_d_bag(Console *self);
//�R���\�[���̃R�}���h���V�t�g�z��Ɋi�[
void console_shift_log(Console *self);

// �������v�Z����
void Console_Update( Console *console );

// �`�悷��
void Console_Draw( Console *console );

// �I������������
void Console_Finalize( Console *console );

#endif