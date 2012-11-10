#include "DxLib.h"
#include "Keyboard.h"
#include "Player.h"

static const int NUM = 2;        //プレイヤーの数

static Player_t m_Player[NUM];    //プレイヤーの実体
static int m_ImgPlayer;            //プレイヤーの画像ハンドル

// 初期化をする
void PlayerMgr_Initialize(){
    m_ImgPlayer = LoadGraph("画像/キャラクタ01.png");

    Player_Initialize( &m_Player[0],   0, m_ImgPlayer );// 初期化
    Player_Initialize( &m_Player[1], 200, m_ImgPlayer );// 初期化
}

// 動きを計算する
void PlayerMgr_Update(){
    for( int i=0; i<NUM; i++ ){
        Player_Update(&m_Player[i]);//更新
    }
}

// 描画する
void PlayerMgr_Draw(){
    for( int i=0; i<NUM; i++ ){
        Player_Draw(m_Player[i]);//描画
    }
}

// 終了処理をする
void PlayerMgr_Finalize(){
    for( int i=0; i<NUM; i++ ){
        Player_Finalize(m_Player[i]);//終了処理
    }

    DeleteGraph( m_ImgPlayer );    //画像を解放
}
