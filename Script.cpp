#include "DxLib.h"
#include "Keyboard.h"
#include "Script.h"

struct Script
{
    
}; 

// 初期化をする
Script *Script_Initialize( int y, int img )
{
	Script *self;
	self = (Script *)malloc(sizeof(Script));
	
	return self;
}

// 動きを計算する
void Script_Update( Script *self )
{
   
}

// 描画する
void Script_Draw( Script *self){
   
}

// 終了処理をする
void Script_Finalize( Script *self )
{
    
}
