#ifndef DEF_KEYBOARD_H //二重include防止

#define DEF_KEYBOARD_H

// キーの入力状態を更新する
void Keyboard_Update();

// 引数のキーコードのキーの入力状態を返す
int Keyboard_Get( int KeyCode );

#endif