#ifndef DEF_PLAYER_H //二重include防止

#define DEF_PLAYER_H

struct Player;

// 初期化をする
Player Player_Initialize( int y, int img );

// 動きを計算する
void Player_Update( Player *Player );

// 描画する
void Player_Draw( Player *Player );

// 終了処理をする
void Player_Finalize( Player *Player );

#endif