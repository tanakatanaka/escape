#ifndef DEF_Twod_H //二重include防止

#define DEF_Twod_H

struct Twod;

// 初期化をする
Twod *Twod_Initialize();
//画像を描画モードにする
void Twod_add_image(Twod *self, int x, int y, int id , const char *tag);
//画像の描画モードを解除
void twod_erase_image(Twod *self, const char *tag);
// 動きを計算する
void Twod_Update( Twod *Twod );
// 描画する
void Twod_Draw( Twod *Twod );
// 終了処理をする
void Twod_Finalize( Twod *Twod );

#endif