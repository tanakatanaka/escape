#ifndef DEF_Console_H //��dinclude�h�~

#define DEF_Console_H

struct Console;

// ������������
Console *Console_Initialize( );

// �������v�Z����
void Console_Update( Console *Console );

// �`�悷��
void Console_Draw( Console *Console );

// �I������������
void Console_Finalize( Console *Console );

#endif