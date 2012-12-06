#include "DxLib.h"
#include "Pad.h"

static char m_Key[256];    // �L�[�̓��͏�Ԋi�[�p�ϐ�
static char old_Key[256];    //��O�̃L�[�̓��͏�Ԋi�[�p�ϐ�

// �������v�Z����
void Pad_Update(  )
{
	char tmpKey[256];            // ���݂̃L�[�̓��͏�Ԃ��i�[����
    GetHitKeyStateAll  ( tmpKey );// �S�ẴL�[�̓��͏�Ԃ𓾂�
    
	for( int i=0; i < 256; i++ )
	{ 
        if( tmpKey[i] != 0 )
		{    // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
            m_Key[i]++;            // ���Z
        }
		else if( old_Key[i] == 1 && tmpKey[i] == 0)
		{
			 m_Key[i] = -1;
		}
		else 
		{                // ������Ă��Ȃ����
            m_Key[i] = 0;            // 0�ɂ���
        }

		old_Key[i] = tmpKey[i];
	}
}

// KeyCode�̃L�[�̓��͏�Ԃ��擾����
int Pad_Get( int KeyCode )
{
    return m_Key[ KeyCode ];
}

