#include "DxLib.h"
#include "Keyboard.h"
#include "Game.h"
#include "Player.h"

// ������������
void Game_Initialize( Game_t *Game)
{
	
}

	


// �������v�Z����
void Game_Update( Game_t *Game )
{
	Keyboard_Update();    //�L�[�{�[�h�̍X�V
    PlayerMgr_Update();    //�v���C���[�Ǘ����W���[���̍X�V
}

// �`�悷��
void Game_Draw( Game_t Game )
{
    PlayerMgr_Draw();    //�v���C���[�Ǘ����W���[���̕`��
}

// �I������������
void Game_Finalize( Game_t Game )
{
	PlayerMgr_Finalize();    //�v���C���[�Ǘ����W���[���̏I������   
}
