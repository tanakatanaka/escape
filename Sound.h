#ifndef DEF_Sound_H //��dinclude�h�~

#define DEF_Sound_H

struct Sound;

// ������������
Sound *Sound_Initialize();

void Sound_type( Sound *self);
void Sound_se( Sound *self, const char *name);

// �I������������
void Sound_Finalize( Sound *Sound );

#endif