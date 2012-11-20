#ifndef DEF_Mess_H //二重include防止

#define DEF_Mess_H

struct Mess;

// 初期化をする
Mess *Mess_Initialize();

// 動きを計算する
void Mess_Update( Mess *Mess );

// 描画する
void Mess_Draw( Mess *Mess );

// 終了処理をする
void Mess_Finalize( Mess *Mess );

#endif