#include "DxLib.h"
#include "Pad.h"

static char m_Key[256];    // �L�[�̓��͏�Ԋi�[�p�ϐ�
int time_count;


// �������v�Z����
void Pad_Update()
{
    char tmpKey[256];            // ���݂̃L�[�̓��͏�Ԃ��i�[����
    GetHitKeyStateAll(tmpKey);    // �S�ẴL�[�̓��͏�Ԃ𓾂�

    for (int i = 0; i < 256; i++)
    {
        if (tmpKey[i] != 0)
        {
            // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
            if (m_Key[i] > 0)
            {
                m_Key[i]++; // ���łɉ����Ă�����Z
            }
            else
            {
                m_Key[i] = 1; // �����Ă���1�ɂ���
            }
        }
        else if (m_Key[i] > 0)  // �������u�Ԃ�-1
        {
            m_Key[i] = -1;
        }
        else
        {
            // ������Ă��Ȃ����
            m_Key[i] = 0;            // 0�ɂ���
        }
    }

	time++;
}

// KeyCode�̃L�[�̓��͏�Ԃ��擾����
int Pad_Get(int KeyCode)
{
    return m_Key[ KeyCode ];
}

