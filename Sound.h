#ifndef DEF_Sound_H //二重include防止

#define DEF_Sound_H

struct Sound;

// 初期化をする
Sound *Sound_Initialize();

void Sound_type( Sound *self, int type);
void Sound_se( Sound *self, const char *name);

// 終了処理をする
void Sound_Finalize( Sound *Sound );

#endif