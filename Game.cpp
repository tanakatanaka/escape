#include "DxLib.h"
#include "Game.h"
#include "Console.h"
#include "Script.h"

static const int NUM = 2;        //�v���C���[�̐�

struct Game
{
	Console *console;
	Script *script;
};

// ������������
Game *Game_Initialize()
{
	Game *self;
	self = (Game *)malloc(sizeof(Game));
	self->console = Console_Initialize( );
	self->script = Script_Initialize( );
	AllocConsole();
	freopen("CONOUT$", "w", stdout); 
	freopen("CONIN$", "r", stdin);


	return self;
}


// �������v�Z����
void Game_Update(Game *self)
{
	Console_Update( self->console );
	Script_Update( self->script );
}

// �`�悷��
void Game_Draw(Game *self)
{
	 
	 Console_Draw( self->console );
	 Script_Draw( self->script );
     
}

// �I������������
void Game_Finalize(Game *self )
{
	
}
