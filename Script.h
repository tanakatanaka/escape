#ifndef DEF_Script_H //��dinclude�h�~

#define DEF_Script_H

struct Script;

// ������������
Script *Script_Initialize();

// �������v�Z����
void Script_Update( Script *Script );

// �`�悷��
void Script_Draw( Script *Script );

// �I������������
void Script_Finalize( Script *Script );

#endif