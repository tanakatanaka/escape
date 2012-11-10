#ifndef DEF_PLAYER_H //二重include防止

#define DEF_PLAYER_H

typedef struct{
    int Image;
    int y;
} Player_t;

// 初期化をする
void Player_Initialize( Player_t *Player, int y, int img );

// 動きを計算する
void Player_Update( Player_t *Player );

// 描画する
void Player_Draw( Player_t Player );

// 終了処理をする
void Player_Finalize( Player_t Player );

#endif