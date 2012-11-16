#ifndef DEF_Console_H //二重include防止

#define DEF_Console_H

struct Console;

// 初期化をする
Console *Console_Initialize( );

// 動きを計算する
void Console_Update( Console *Console );

// 描画する
void Console_Draw( Console *Console );

// 終了処理をする
void Console_Finalize( Console *Console );

#endif