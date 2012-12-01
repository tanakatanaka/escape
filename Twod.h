#ifndef DEF_Twod_H //二重include防止

#define DEF_Twod_H

struct Twod;

// 初期化をする
Twod *Twod_Initialize();
//画像を描画モードにする
void Set_tags(Twod *self, char tag, int x, int y);
// 動きを計算する
void Twod_Update( Twod *Twod );
// 描画する
void Twod_Draw( Twod *Twod );
// 終了処理をする
void Twod_Finalize( Twod *Twod );

#endif