#ifndef DEF_Console_H //二重include防止

#define DEF_Console_H

struct Console;

// 初期化をする
Console *Console_Initialize( );

//コンソールの閉じてる開いてるを表示
int console_state(Console *self);
//コンソールの文字を返す関数
const char *console_d_bag(Console *self);
//コンソールのコマンドをシフト配列に格納
void console_shift_log(Console *self);

// 動きを計算する
void Console_Update( Console *console );

// 描画する
void Console_Draw( Console *console );

// 終了処理をする
void Console_Finalize( Console *console );

#endif