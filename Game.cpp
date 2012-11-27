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
	AllocConsole();
	freopen("CONOUT$", "w", stdout); 
	freopen("CONIN$", "r", stdin);

	Game *self;
	self = (Game *)malloc(sizeof(Game));
	self->console = Console_Initialize( );
	self->script = Script_Initialize( );
	
	return self;
}


// �������v�Z����
void Game_Update(Game *self)
{
	Script_Update( self->script );
	Console_Update( self->console );
	
}

// �`�悷��
void Game_Draw(Game *self)
{
	 Script_Draw( self->script );
	 Console_Draw( self->console );
	 
     
}

// �I������������
void Game_Finalize(Game *self )
{
	
}
