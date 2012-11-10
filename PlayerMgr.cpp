#include "DxLib.h"
#include "Keyboard.h"
#include "Player.h"

static const int NUM = 2;        //�v���C���[�̐�

static Player_t m_Player[NUM];    //�v���C���[�̎���
static int m_ImgPlayer;            //�v���C���[�̉摜�n���h��

// ������������
void PlayerMgr_Initialize(){
    m_ImgPlayer = LoadGraph("�摜/�L�����N�^01.png");

    Player_Initialize( &m_Player[0],   0, m_ImgPlayer );// ������
    Player_Initialize( &m_Player[1], 200, m_ImgPlayer );// ������
}

// �������v�Z����
void PlayerMgr_Update(){
    for( int i=0; i<NUM; i++ ){
        Player_Update(&m_Player[i]);//�X�V
    }
}

// �`�悷��
void PlayerMgr_Draw(){
    for( int i=0; i<NUM; i++ ){
        Player_Draw(m_Player[i]);//�`��
    }
}

// �I������������
void PlayerMgr_Finalize(){
    for( int i=0; i<NUM; i++ ){
        Player_Finalize(m_Player[i]);//�I������
    }

    DeleteGraph( m_ImgPlayer );    //�摜�����
}
