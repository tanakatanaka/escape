#include "DxLib.h"
#include <string>
#include "Console.h"
#include "Pad.h"

static const float moji[] =
{
	D_DIK_A, D_DIK_B, D_DIK_C, D_DIK_D, D_DIK_E,
	D_DIK_F, D_DIK_G, D_DIK_H, D_DIK_I, D_DIK_J,
	D_DIK_K, D_DIK_L, D_DIK_M, D_DIK_N, D_DIK_O,
	D_DIK_P, D_DIK_Q, D_DIK_R, D_DIK_S, D_DIK_T,
	D_DIK_U, D_DIK_V, D_DIK_W, D_DIK_X, D_DIK_Y,
	D_DIK_Z
};

struct Console
{
	int win_s;
	int blue ;
	int green;
	std::string d_bag;
}; 

// 初期化をする
Console *Console_Initialize()
{
	Console *self;
	self =  new Console();
	self->win_s = 0;
	self->blue = GetColor( 0 , 0 , 200 ) ;
	self->green = GetColor( 0, 255, 0 );
	return self;
}

int Console_over(Console *self)
{
	return self->win_s % 2;
}

static float get_chara()
{
	for (int i = 0; i < 26; i++)
  	{
	    if (Pad_Get( KEY_INPUT_A + i ) == -1)
	    {
			return  moji[i];
	    }
	}
  return -1;
}


// 動きを計算する
void Console_Update( Console *self )
{
	
	if(Pad_Get(KEY_INPUT_ESCAPE) == 1 ){self->win_s++;}


	if(self->win_s % 2 == 1)
	{
		float bag = get_chara();

		if(bag == -1)
		{
			//入力がない場合
		}
		else if(Pad_Get( KEY_INPUT_BACK ) == -1)
		{
			//バックスペース入力があった場合
			//最後の文字を消去
			self->d_bag.erase(self->d_bag.size() - 1);

		}
		else
		{
			//文字入力があった場合追加
			self->d_bag += (char) bag;
		}
		
	}

}

// 描画する
void Console_Draw( Console *self)
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 ) ;
	if(self->win_s % 2 == 0)
	{
		DrawBox( 0, 420 , 640 , 480, self->blue, TRUE) ;
	}
	else
	{
		DrawBox( 0, 380 , 640 , 480, self->blue, TRUE) ;
		DrawFormatString( 10, 10, self->green, "%s", self->d_bag.c_str()); // 文字を描画する
	}
}

// 終了処理をする
void Console_Finalize( Console *self )
{
	
}
