#include "DxLib.h"
#include "Twod.h"

struct Twod
{

}; 

// 初期化をする
Twod *Twod_Initialize(  )
{
	Twod *self;
	self = (Twod *)malloc(sizeof(Twod));
	return self;
}

// 動きを計算する
void Twod_Update( Twod *self )
{
	
}

// 描画する
void Twod_Draw( Twod *self)
{
    
}

// 終了処理をする
void Twod_Finalize( Twod *self )
{
    
}
