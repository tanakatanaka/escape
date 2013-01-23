#ifndef DEF_Script_H //二重include防止

#define DEF_Script_H
#include "Camera.h"
#include "Console.h"

struct Script;

// 初期化をする
Script *Script_Initialize(Camera *self, Console *console);

//スクリプトに現在位置を設定する
void Script_set_area(Script *self, int area);
//スクリプトに現在の方角を設定する
void Script_set_hougaku(Script *self, int hougaku);


// 動きを計算する
void Script_Update( Script *Script );

// 描画する
void Script_Draw( Script *Script );

// 終了処理をする
void Script_Finalize( Script *Script );

#endif