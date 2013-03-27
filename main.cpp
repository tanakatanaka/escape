#include "DxLib.h"
#include "Game.h"
#include "Pad.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    AllocConsole();
    freopen("CONOUT$", "w", stdout); 
    freopen("CONOUT$", "w", stderr);
    freopen("CONIN$", "r", stdin);

    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

    Game *game = Game_Initialize();

    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0)
    {
        Pad_Update();
		if(Game_Update(game) == false){break;}
        Game_Draw(game);
    }

    Game_Finalize(game);

    DxLib_End();
    return 0;
}
