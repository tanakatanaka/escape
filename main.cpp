#include "DxLib.h"
#include "Game.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
    ChangeWindowMode(TRUE),DxLib_Init(),SetDrawScreen( DX_SCREEN_BACK );

	Game_t Game = Game_Initialize();

    while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 )
	{
		Game_Update( Game_t *Game );
		Game_Draw( Game_t Game );

    }

	Game_Finalize( Game_t Game );

    DxLib_End();
    return 0;
}
