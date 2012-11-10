#ifndef DEF_Game_H //二重include防止

#define DEF_Game_H

typedef struct{
    
} Game_t;

// 初期化をする
void Game_Initialize( Game_t *Game);

// 動きを計算する
void Game_Update( Game_t *Game );

// 描画する
void Game_Draw( Game_t Game );

// 終了処理をする
void Game_Finalize( Game_t Game );

#endif