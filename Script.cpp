#include "DxLib.h"
#include <string>
#include <deque>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "Console.h"
#include "Script.h"
#include "Camera.h"
#include "Room.h"
#include "Player.h"
#include "Mess.h"
#include "Twod.h"
#include "Pad.h"


typedef std::vector<std::string> Words;
typedef std::istream_iterator<std::string> I;
using std::istringstream;
using std::copy;


struct Condition_order
{
	//命令条件の構造体
	//管理番号・場所・方角・命令内容・命令対象

	int num;
	int area;
	int hougaku;
	std::string order;
	std::string object;

};

struct Effect_order
{
	//命令効果の構造体
	//x,y,効果番号(0:画像表示 1:文字表示 2:消去)
	int num;
	int x;
	int y;
	int effect_num;
};

struct Script
{

	Room *room;
    Camera *camera;
    Mess *mess;
	Twod *twod;
	Console *console;

	//命令構造体変数 
	std::vector<Condition_order> condition_order;
	std::vector<Effect_order> effect_order;
	
};

void pack_words(Script *self, Words one_words)
{
	printf("\n 1 \n");

	for(int i = 0; i < one_words.size() - 1; i++)
	{
		if(one_words[0] == "jojo")
		{
			printf("\n lalala \n");
		}

	}

}

int load_script(Script *self, const char *filename)
{
	int pos = 0; //現在の文字位置
	int now_line = 0; //現在の行位置
	int block = 0;	//現在のブロック位置
	char c; //1文字
	std::vector<std::string> one_words;
	FILE* fp; //スクリプトファイル

	fp = fopen(filename, "r"); //スクリプトファイルを開く

	if(fp == NULL )
	{
		//ファイル読み込みに失敗
		printf("スクリプト %s を読み込めませんでした\n", filename);
		return -1;
	}

	while(1) 
	{
		c = fgetc( fp ); //一文字読み込み
		
		if( feof( fp ) ) { break;} //ファイルの終わりかどうか
		
		//文章先頭の空白部分を読み飛ばす
		while( (c == ' ' || c == '\t') && pos == 0 && !feof( fp ) ) 
		{
			block++;
			c = fgetc( fp );
		}

		//改行文字がでるまで
		if( c != '\n' ) 
		{
			one_words[block] += c; //1単語に1文字追加
			pos++;//文字書き込み位置をずらす
		}
		else 
		{
			//空行は読み飛ばす
			if( pos == 0 ) { continue; }

			//改行文字が出たら次の行へ
			//その際に,その行の単語達を詰める関数へ,そして行位置・文字位置・ブロック位置をリセット
			pack_words(self, one_words);
			now_line++; //次の行に移動
			pos = 0; //現在の文字位置を0に
			block = 0; //現在のブロックを0に
		}
	
	

	}
	return 0;
}



// 初期化をする
Script *Script_Initialize(Camera *camera, Console *console , Player *player)
{
	Script *self;
	self = new Script();

	self->camera = camera;
	self->room = Room_Initialize();
	self->mess = Mess_Initialize( );
	self->twod = Twod_Initialize( );
	self->console = console;

	printf("\nスクリプト読み込み　開始\n\n");
	//load_script(self, "tex/script.txt");

	return self;
}





Words split(const char *str)
{
    istringstream ss(str);
    Words words;
    copy(I(ss), I(), std::back_inserter<Words>(words));
    return words;
}

void word_act(Script *self, Words &words)
{	

}

void decode_command(Script *self)
{
	if(Pad_Get( KEY_INPUT_RETURN ) == -1)
	{
		//単語後に分解
		const char *command = console_d_bag(self->console);
		
		if(command != NULL)
		{
			Words words = split(command);
			//コンソールのほうにあるコマンドをログに移動
			console_shift_log(self->console);
			//分解したwordを解読関数にかける
			word_act(self,words);
		}
	}
}


// 動きを計算する
void Script_Update( Script *self )
{
	Room_Update( self->room );
	Mess_Update( self->mess );
	Twod_Update( self->twod );

	decode_command(self);

	
}	

// 描画する
void Script_Draw( Script *self)
{
	
	Room_Draw(self->room);
	Twod_Draw( self->twod );
	Mess_Draw(self->mess);
	
}

// 終了処理をする
void Script_Finalize( Script *self )
{
    
}
