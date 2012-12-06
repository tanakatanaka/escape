#include "DxLib.h"
#include "Console.h"
#include "Pad.h"



struct Console
{
	int cr ;
	int win_s;
	char d_bag;
	int green;
}; 

// 初期化をする
Console *Console_Initialize()
{
	Console *self;
	self = (Console *)malloc(sizeof(Console));
	self->cr = GetColor( 0 , 0 , 200 ) ;
	self->win_s = 0;
	self->green = GetColor( 0, 255, 0 );
	self->d_bag += 'a';
	return self;
}

static int get_chara()
{
	int key = KEY_INPUT_A;
	for (int i = 0; i < 26; i++)
  	{
	    if (Pad_Get( key+1 ) == -1)
	    {
			printf("\nmoji:%c\n",key);
	    	return key + i;
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
		else if(Pad_Get( KEY_INPUT_BACK ))
		{
			//バックスペース入力があった場合
			//最後の文字を消去
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
		DrawFormatString( 10, 10, self->green, "%s", self->d_bag); // 文字を描画する
	}
}

// 終了処理をする
void Console_Finalize( Console *self )
{
	
}
