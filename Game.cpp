#include "DxLib.h"
#include "Keyboard.h"
#include "Game.h"
#include "Room.h"


static const int NUM = 2;        //�v���C���[�̐�

struct Game
{
	Room *room;

};

// ������������
Game *Game_Initialize()
{
	Game *self;
	int gazo = LoadGraph("�摜/�L�����N�^01.png");
	self = (Game *)malloc(sizeof(Game));
	self->room = Room_Initialize();

	return self;
}


// �������v�Z����
void Game_Update(Game *self)
{
	Keyboard_Update();    //�L�[�{�[�h�̍X�V
	
	for( int i=0; i<NUM; i++ )
	{
        
    }
}

// �`�悷��
void Game_Draw(Game *self)
{
	 Room_Draw(self->room);
   
}

// �I������������
void Game_Finalize(Game *self )
{
	for( int i=0; i<NUM; i++ )
	{
          
    }
	
}
