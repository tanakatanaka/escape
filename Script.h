#ifndef DEF_Script_H //��dinclude�h�~

#define DEF_Script_H
#include "Camera.h"
#include "Console.h"

struct Script;

// ������������
Script *Script_Initialize(Camera *self, Console *console);

// �������v�Z����
void Script_Update( Script *Script );

// �`�悷��
void Script_Draw( Script *Script );

// �I������������
void Script_Finalize( Script *Script );

#endif