#ifndef DEF_Script_H //��dinclude�h�~

#define DEF_Script_H
#include "Camera.h"
#include "Console.h"

struct Script;

// ������������
Script *Script_Initialize(Camera *self, Console *console);

//�X�N���v�g�Ɍ��݈ʒu��ݒ肷��
void Script_set_area(Script *self, int area);
//�X�N���v�g�Ɍ��݂̕��p��ݒ肷��
void Script_set_hougaku(Script *self, int hougaku);


// �������v�Z����
void Script_Update( Script *Script );

// �`�悷��
void Script_Draw( Script *Script );

// �I������������
void Script_Finalize( Script *Script );

#endif