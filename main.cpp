#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int)
{
    ChangeWindowMode(TRUE),DxLib_Init(),SetDrawScreen( DX_SCREEN_BACK );

	Game *game = Game_Initialize();

    while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 )
	{
		Game_Update(game);
		Game_Draw(game );
		Pad_Update();
    }

	Game_Finalize(game);

    DxLib_End();
    return 0;
}
