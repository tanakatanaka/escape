#ifndef DEF_Pad_H //��dinclude�h�~

#define DEF_Pad_H

struct Pad;

// ������������
Pad *Pad_Initialize( );

// �������v�Z����
void Pad_Update( Pad *Pad );


// �I������������
void Pad_Finalize( Pad *Pad );

#endif