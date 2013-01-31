#ifndef DEF_Camera_H //二重include防止

#define DEF_Camera_H

struct Camera;

// 初期化をする
Camera *Camera_Initialize( );

//gameから現在の位置をもらう関数
void Camera_set_area(Camera *self, int area);
//gameから左右回転をもらう関数
void Camera_set_muki(Camera *self, int muki);
//cameraの方角をもらう関数;
int Camera_set_muki(Camera *self);

//カメラの視点モードの有無を返す
int Camera_is_look_at(Camera *self);

/*gameからカメラモード(歩行・視点)をもらう関数
もし視点モードになる場合方角をもらう*/
int Camera_set_camera_mode(Camera *self, int camera_mode);
//視点操作の値を回収..type0:x,type1:y
void Camera_set_pt(Camera *self, int type, float point);
// 動きを計算する
void Camera_Update( Camera *Camera );

// 描画する
void Camera_Draw( Camera *Camera );

// 終了処理をする
void Camera_Finalize( Camera *Camera );

#endif