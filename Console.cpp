#include "DxLib.h"
#include <string>
#include "Console.h"
#include "Pad.h"



struct Console
{
	int cr ;
	int win_s;
	std::string d_bag;
	int green;
}; 

// 初期化をする
Console *Console_Initialize()
{
	Console *self;
	self =  new Console();
	self->cr = GetColor( 0 , 0 , 200 ) ;
	self->win_s = 0;
	self->green = GetColor( 0, 255, 0 );
	return self;
}

static int get_chara()
{
	for (int i = 0; i < 26; i++)
  	{
	    if (Pad_Get( KEY_INPUT_A + i ) == -1)
	    {
			return 'a' + i;
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
		int bag = get_chara();

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
		DrawBox( 0, 420 , 640 , 480, self->cr, TRUE) ;
	}
	else
	{
		DrawBox( 0, 380 , 640 , 480, self->cr, TRUE) ;
		DrawFormatString( 10, 10, self->green, "%s", self->d_bag.c_str()); // 文字を描画する
	}
}

// 終了処理をする
void Console_Finalize( Console *self )
{
	
}
