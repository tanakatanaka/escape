#include "DxLib.h"
#include "Keyboard.h"
#include "Game.h"
#include "Room.h"
#include "Camera.h"
#include "Console.h"
#include "Mess.h"
#include "Script.h"

static const int NUM = 2;        //プレイヤーの数

struct Game
{
	Room *room;
	Camera *camera;
	Console *console;
	Mess *mess;
	Script *script;

};

// 初期化をする
Game *Game_Initialize()
{
	Game *self;
	self = (Game *)malloc(sizeof(Game));
	self->camera = Camera_Initialize( );
	self->room = Room_Initialize();
	self->console = Console_Initialize( );
	self->mess = Mess_Initialize( );
	self->script = Script_Initialize( );
	AllocConsole();
	freopen("CONOUT$", "w", stdout); 
	freopen("CONIN$", "r", stdin);


	return self;
}


// 動きを計算する
void Game_Update(Game *self)
{
	
	Camera_Update(self->camera);
	Keyboard_Update();    //キーボードの更新
	Room_Update( self->room );
	Console_Update( self->console );
	//Mess_Update( self->mess );
	Script_Update( self->script );


}

// 描画する
void Game_Draw(Game *self)
{
	 Room_Draw(self->room);
	 Console_Draw( self->console );
	 //Mess_Draw(self->mess);
	 Script_Draw( self->script );
     
}

// 終了処理をする
void Game_Finalize(Game *self )
{
	
}
