#include "DxLib.h"
#include <string>
#include <deque>
#include "Console.h"
#include "Pad.h"

static const int KEYCODES[] =
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
	int win_c;
	int moji_c;
	int x;
	int y;
	std::string d_bag;
	std::deque<std::string> log;
}; 

// 初期化をする
Console *Console_Initialize()
{
	Console *self;
	self =  new Console();
	self->win_s = 0;
	self->win_c = GetColor( 0 , 0 , 200 );
	self->moji_c = GetColor( 0, 255, 0 );
	self->x = 0;
	self->y = 420;

	return self;
}

int Console_over(Console *self)
{
	return self->win_s % 2;
}

static int get_chara()
{
	for (int i = 0; i < 26; i++)
  	{
	    if (Pad_Get( KEYCODES[i] ) == -1)
	    {
			return  'a'+ i;
	    }
	}
	//バックスペース入力があった場合
	if(Pad_Get( KEY_INPUT_BACK ) == -1){return -2;}

	//エンター入力があった場合
	if(Pad_Get( KEY_INPUT_RETURN ) == -1){return -3;}

	//スペース入力があった場合
	if(Pad_Get( KEY_INPUT_SPACE ) == -1){return ' ';}



  //入力がなかった場合
  return -1;
}

void split_string(char *code)
{
	char *tp;
	char *box[10];
	printf("\ncode = %s\n",code);

	for(int i = 0; i < 2 ; i++ )
	{
		//分割対象文字列が無くなるまで分割
		if( (box[i] = strtok(code, " ")) == NULL )
		{
			break;
		}

		printf("\narea = %s\n",box[i]);
		//2回目にstrtokを呼び出す時は，cpをNULLにする
		code = NULL;
	}
        
		
		
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
		else if(bag == -2)
		{
			//バックスペース入力があった場合
			//最後の文字を消去
			self->d_bag.erase(self->d_bag.size() - 1);

		}
		else if(bag == -3)
		{
			//エンター入力があった場合
			self->log.push_back(self->d_bag);
			char code[100];
			strcpy( code,self->d_bag.c_str() );
			split_string(code);
			self->d_bag.erase(0);

		}
		else
		{
			//文字入力があった場合追加
			self->d_bag += (char) bag;
		}
		
	}
	else
	{
		//コンソールとき	
	}

}

// 描画する
void Console_Draw( Console *self)
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 ) ;
	
	int plus;
	if(self->win_s % 2 == 1){plus = -40;}
	else{plus = 0;}

	DrawBox( 0, 420 +  plus, 640 , 480, self->win_c, TRUE) ;
	
	
	DrawFormatString( self->x, 465 - 15, self->moji_c, "%s", self->log); // logを描画する
	DrawFormatString( self->x, 465, self->moji_c, "%s", self->d_bag.c_str()); // 現在の文字を描画する
}

// 終了処理をする
void Console_Finalize( Console *self )
{
	
}
