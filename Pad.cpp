#include "DxLib.h"
#include "Pad.h"

struct Pad
{
   
}; 

// 初期化をする
Pad *Pad_Initialize( )
{
	Pad *self;
	self = (Pad *)malloc(sizeof(Pad));
	return self;
}

// 動きを計算する
void Pad_Update( Pad *self )
{
    
}


// 終了処理をする
void Pad_Finalize( Pad *self )
{
    
}
