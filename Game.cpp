#include "DxLib.h"
#include "Keyboard.h"
#include "Game.h"
#include "PlayerMgr.h"

static const int NUM = 2;        //�v���C���[�̐�

struct Game
{
	Player *player[2];

};

// ������������
Game Game_Initialize()
{
	Game *self;
	int gazo = LoadGraph("�摜/�L�����N�^01.png");
	self = (Game *)malloc(sizeof(Game));
	self->player[0] = Player_Initialize(10, gazo);
	self->player[1] = Player_Initialize(50, gazo);

	return *self;
}


// �������v�Z����
void Game_Update( Game *Game )
{
	Keyboard_Update();    //�L�[�{�[�h�̍X�V
	
	for( int i=0; i<NUM; i++ )
	{
        Player_Update(self->player[NUM]);//�X�V
    }
}

// �`�悷��
void Game_Draw( Game Game )
{
	for( int i=0; i<NUM; i++ )
	{
         PlayerMgr_Draw(self->player[NUM]);    //�v���C���[�Ǘ����W���[���̕`��
    }
   
}

// �I������������
void Game_Finalize( Game Game )
{
	for( int i=0; i<NUM; i++ )
	{
         PlayerMgr_Finalize(self->player[NUM]);    //�v���C���[�Ǘ����W���[���̏I������   
    }
	
}
