#include "DxLib.h"
#include "Pad.h"

static char m_Key[256];    // キーの入力状態格納用変数
int time_count;


// 動きを計算する
void Pad_Update()
{
    char tmpKey[256];            // 現在のキーの入力状態を格納する
    GetHitKeyStateAll(tmpKey);    // 全てのキーの入力状態を得る

    for (int i = 0; i < 256; i++)
    {
        if (tmpKey[i] != 0)
        {
            // i番のキーコードに対応するキーが押されていたら
            if (m_Key[i] > 0)
            {
                m_Key[i]++; // すでに押してたら加算
            }
            else
            {
                m_Key[i] = 1; // 離してたら1にする
            }
        }
        else if (m_Key[i] > 0)  // 離した瞬間は-1
        {
            m_Key[i] = -1;
        }
        else
        {
            // 押されていなければ
            m_Key[i] = 0;            // 0にする
        }
    }

	time++;
}

// KeyCodeのキーの入力状態を取得する
int Pad_Get(int KeyCode)
{
    return m_Key[ KeyCode ];
}

