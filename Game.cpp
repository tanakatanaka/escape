#include "DxLib.h"
#include "Game.h"
#include "Script.h"

static const int NUM = 2;        //�v���C���[�̐�

struct Game
{
	Script *script;
};

// ������������
Game *Game_Initialize()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout); 
	freopen("CONIN$", "r", stdin);

	Game *self;
	self = (Game *)malloc(sizeof(Game));
	self->script = Script_Initialize( );
	
	return self;
}


// �������v�Z����
void Game_Update(Game *self)
{
	Script_Update( self->script );
	
	
}

// �`�悷��
void Game_Draw(Game *self)
{
	 Script_Draw( self->script );
	 
	 
     
}

// �I������������
void Game_Finalize(Game *self )
{
	
}
