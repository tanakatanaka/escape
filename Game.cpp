#include "DxLib.h"
#include "Keyboard.h"
#include "Game.h"
#include "Room.h"
#include "Camera.h"
#include "Console.h"

static const int NUM = 2;        //�v���C���[�̐�

struct Game
{
	Room *room;
	Camera *camera;
	Console *console;

};

// ������������
Game *Game_Initialize()
{
	Game *self;
	int gazo = LoadGraph("�摜/�L�����N�^01.png");
	self = (Game *)malloc(sizeof(Game));
	self->camera = Camera_Initialize( );
	self->room = Room_Initialize();
	self->console = Console_Initialize( );
	return self;
}


// �������v�Z����
void Game_Update(Game *self)
{
	Camera_Update(self->camera);
	Keyboard_Update();    //�L�[�{�[�h�̍X�V
	Room_Update( self->room );
	Console_Update( self->console );
}

// �`�悷��
void Game_Draw(Game *self)
{
	 Room_Draw(self->room);
	 Console_Draw( self->console );
     
}

// �I������������
void Game_Finalize(Game *self )
{
	
}
