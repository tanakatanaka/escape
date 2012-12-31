#ifndef DEF_Camera_H //二重include防止

#define DEF_Camera_H

struct Camera;

// 初期化をする
Camera *Camera_Initialize( );

void Camera_get_area(Camera *self, int area);

// 動きを計算する
void Camera_Update( Camera *Camera );

// 描画する
void Camera_Draw( Camera *Camera );

// 終了処理をする
void Camera_Finalize( Camera *Camera );

#endif