#ifndef DEF_Console_H //二重include防止

#define DEF_Console_H

struct Console;

// 初期化をする
Console *Console_Initialize( );

//コンソールの閉じてる開いてるを表示
int console_state(Console *self);
//コンソールの文字を返す関数
const char *console_d_bag(Console *self);

// 動きを計算する
void Console_Update( Console *Console );

// 描画する
void Console_Draw( Console *Console );

// 終了処理をする
void Console_Finalize( Console *Console );

#endif