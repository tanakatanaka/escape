#ifndef DEF_ENDING_H //二重include防止

#define DEF_ENDING_H

struct Ending;

// 初期化をする
Ending *Ending_Initialize();

// 動きを計算する
void Ending_Update( Ending *Ending );

// 描画する
void Ending_Draw( Ending *Ending );

// 終了処理をする
void Ending_Finalize( Ending *Ending );

#endif