#ifndef DEF_COMPILER_H //��dinclude�h�~

#define DEF_COMPILER_H

struct Compiler;

// ������������
Compiler *Compiler_Initialize();

// �������v�Z����
void Compiler_Update( Compiler *Compiler );

// �`�悷��
void Compiler_Draw( Compiler *Compiler );

// �I������������
void Compiler_Finalize( Compiler *Compiler );

#endif