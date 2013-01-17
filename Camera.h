#ifndef DEF_Camera_H //二重include防止

#define DEF_Camera_H

struct Camera;

// 初期化をする
Camera *Camera_Initialize( );

//gameから現在の位置をもらう関数
void Camera_get_area(Camera *self, int area);
//gameから左右回転をもらう関数
void Camera_get_muki(Camera *self, int muki);
/*gameからカメラモード(歩行・視点)をもらう関数
もし視点モードになる場合方角をもらう*/
void Camera_get_camera_mode(Camera *self, int camera_mode, int hougaku);
// 動きを計算する
void Camera_Update( Camera *Camera );

// 描画する
void Camera_Draw( Camera *Camera );

// 終了処理をする
void Camera_Finalize( Camera *Camera );

#endif