#include "DxLib.h"
#include "Game.h"
#include "Console.h"
#include "Script.h"
#include "Pad.h"
#include "Camera.h"

static const int NUM = 2;        //プレイヤーの数

struct Game
{
	Script *script;
	Camera *camera;
	Console *console;
	int hougaku;
	int area;
	int count;
	int mode;
};

// 初期化をする
Game *Game_Initialize()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout); 
	freopen("CONIN$", "r", stdin);

	Game *self;
	self = (Game *)malloc(sizeof(Game));
	self->camera = Camera_Initialize();
	self->console = Console_Initialize();
	self->script = Script_Initialize(self->camera, self->console);
	self->hougaku = 0;
	self->area = 0;
	self->count = 30;
	self->mode = 0;
	return self;
}

void move_area(Game *self)
{
	if(self->hougaku == 0)
	{
		if(self->area > -1 && self->area < 3 ){self->area++;}
		else if(self->area > 5 && self->area < 8 ){self->area--;}
	}
	else if(self->hougaku == 1){if(self->area > 2 && self->area < 5 ){self->area++;}}
	else if(self->hougaku == 2)
	{
		if(self->area > 4 && self->area < 7 ){self->area++;}
		else if(self->area > 1 && self->area < 4 ){self->area--;}
	}
	else if(self->hougaku == 3){if(self->area > 3 && self->area < 6 ){self->area--;}}

	Camera_get_area(self->camera, self->area);
}



// 動きを計算する
void Game_Update(Game *self)
{
	if(self->mode % 2 == 0)
	{
		if(Pad_Get( KEY_INPUT_RIGHT ) == -1)
		{
			Camera_get_muki(self->camera, 1);
			if(self->hougaku == 3){self->hougaku = 0;}
			else{self->hougaku++;}
		}
		else if(Pad_Get( KEY_INPUT_LEFT ) == -1)
		{
			Camera_get_muki(self->camera, 2);
			if(self->hougaku == 0){self->hougaku = 3;}
			else{self->hougaku--;}
		}
	
		if(self->count > 30 && Pad_Get( KEY_INPUT_UP ) == -1)
		{
			self->count = 0;
			move_area(self);
		}
	}

	if(Pad_Get(KEY_INPUT_ESCAPE) == 1){self->mode++; Console_get_mode(self->console,self->mode);}


	Script_Update( self->script );
	self->count++;
}

// 描画する
void Game_Draw(Game *self)
{
	 Script_Draw( self->script );
	 
	 
     
}

// 終了処理をする
void Game_Finalize(Game *self )
{
	
}
