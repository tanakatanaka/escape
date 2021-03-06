#ifndef DEF_Back_H //二重include防止

#define DEF_Back_H

struct Back;

#include "Camera.h"

// 初期化をする
Back *Back_Initialize(Camera *camera);

// 動きを計算する
void Back_Update( Back *Back );

// 描画する
void Back_Draw( Back *Back );

// 終了処理をする
void Back_Finalize( Back *Back );

#endif