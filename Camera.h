#ifndef DEF_Camera_H //二重include防止

#define DEF_Camera_H

struct Camera;

#include "console.h"

// 初期化をする
Camera *Camera_Initialize( Console *console );

//gameから現在の位置をもらう関数
void Camera_set_area(Camera *self, int area);
//左右回転を返す関数(player_cameraによって返り値が変化)
int Camera_get_hougaku(Camera *self);
//カメラの視点モードの有無を返す
int Camera_is_look_at(Camera *self);

// 動きを計算する
void Camera_Update( Camera *Camera );

// DXのカメラをを設定する
void Camera_Draw( Camera *Camera );

// 背景用に位置指定抜きでDXのカメラを設定する
void Camera_Draw_back(Camera *self);

// 終了処理をする
void Camera_Finalize( Camera *Camera );

#endif