#ifndef DEF_Pad_H //二重include防止

#define DEF_Pad_H

struct Pad;

// 初期化をする
Pad *Pad_Initialize( );

// 動きを計算する
void Pad_Update( Pad *Pad );


// 終了処理をする
void Pad_Finalize( Pad *Pad );

#endif