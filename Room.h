#ifndef DEF_Room_H //二重include防止

#define DEF_Room_H

struct Room;

// 初期化をする
Room *Room_Initialize();

//doorの開閉条件をもらう関数
void Room_set_open(Room *self, int open_close);

// 動きを計算する
void Room_Update( Room *Room );

// 描画する
void Room_Draw( Room *Room );

// 終了処理をする
void Room_Finalize( Room *Room );

#endif