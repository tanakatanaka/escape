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
	int siten_hougaku;
	int area;
	int count;
	int consele_mode;
	int camera_mode;
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
	self->consele_mode = 0;
	self->camera_mode = 0;
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

	Camera_set_area(self->camera, self->area);
}



// 動きを計算する
void Game_Update(Game *self)
{
	if(self->consele_mode % 2 == 0)
	{
		//歩行もしくはカメラ操作状態
		if(self->camera_mode % 2 == 0)
		{
			//歩行状態
			if(Pad_Get( KEY_INPUT_RIGHT ) == -1)
			{
				Camera_set_muki(self->camera, 1);
				if(self->hougaku == 3){self->hougaku = 0;}
				else{self->hougaku++;}
			}
			else if(Pad_Get( KEY_INPUT_LEFT ) == -1)
			{
				Camera_set_muki(self->camera, 2);
				if(self->hougaku == 0){self->hougaku = 3;}
				else{self->hougaku--;}
			}
	
			if(self->count > 30 && Pad_Get( KEY_INPUT_UP ) == -1)
			{
				self->count = 0;
				move_area(self);
			}
		}
		else if(self->camera_mode % 2 == 1)
		{
			//カメラ操作状態
			float move_point = 0.04;

			if(CheckHitKey(KEY_INPUT_UP)){Camera_set_pt(self->camera, 0, -move_point);}
			else if(CheckHitKey(KEY_INPUT_DOWN)){Camera_set_pt(self->camera, 0, +move_point);}

			if(CheckHitKey(KEY_INPUT_RIGHT)){Camera_set_pt(self->camera, 1, move_point);}
			else if(CheckHitKey(KEY_INPUT_LEFT)){Camera_set_pt(self->camera, 1, -move_point);}

		}

		if(Pad_Get( KEY_INPUT_Z ) == -1)
		{
			self->camera_mode++;
			self->hougaku = Camera_set_camera_mode(self->camera, self->camera_mode);
		}
	}

	//どんなモードでも
	if(Pad_Get(KEY_INPUT_ESCAPE) == 1)
	{
		self->consele_mode++; 
		Console_set_mode(self->console,self->consele_mode);

		if(self->camera_mode % 2 == 1)
		{
			self->siten_hougaku = (Camera_set_muki(self->camera) + self->hougaku) % 4;
			if(self->siten_hougaku  < 0){self->siten_hougaku  = 4 + self->siten_hougaku ;}
			printf("\nhougaku = %d\n",self->siten_hougaku);
		}
	}

	if(Pad_Get(KEY_INPUT_F) == 1){printf("\nrote = %d\n",self->hougaku);}

	Script_set_area(self->script, self->area);
	Script_set_hougaku(self->script, self->hougaku);
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
