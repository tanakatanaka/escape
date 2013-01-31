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

//スクリプトは最大1000行まで読み込む
#define SCRIPT_MAX_LINE 1000
//スクリプト最大文字数
#define SCRIPT_MAX_STRING_LENGTH 300

typedef std::vector<std::string> Words;
typedef std::istream_iterator<std::string> I;
using std::istringstream;
using std::copy;



struct Script
{
	Room *room;
    Camera *camera;
    Mess *mess;
	Twod *twod;
	Console *console;
    int maxLineNumber;			//スクリプト行数
	int currentLine;			//現在何行目を実行しているか
	const char* filename;		//ファイル名
	char script[SCRIPT_MAX_LINE][SCRIPT_MAX_STRING_LENGTH];
	char *word[10];
	//プレイヤー情報
	int area;
	int hougaku;
	//命令条件をもつ変数 
	std::vector<int> draw_order;
	std::vector<int> word_order;
};

int loadScript(const char* filename, Script *script);
int decodeScript(const char* scriptMessage, Script *script);
void splitString(const char* src, char* dest[], const char* delim, int splitNum);

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

	self->draw_order.resize(100, 0);
	self->word_order.resize(100, 0);

	printf("\nスクリプト開始\n\n");
	loadScript( "tex/script.txt", self );
	return self;
}



//スクリプトファイルを読み込む
//戻り値 -1 : 失敗  0 : 成功
int loadScript(const char* filename, Script *script)
{
	int pos;
	char c;
	//スクリプトファイル
	FILE* fp;

	//スクリプトファイルを開く
	fp = fopen(filename, "r");

	if(fp == NULL )
	{
		//ファイル読み込みに失敗
		printf("スクリプト %s を読み込めませんでした\n", filename);
		return -1;
	}

	//script書き込み時に使用
	pos = 0;
	for( ;; ) {
		//一文字読み込み
		c = fgetc( fp );
		//ファイルの終わりかどうか
		if( feof( fp ) ) {
			break;
		}
		//文章先頭の空白部分を読み飛ばす
		while( (c == ' ' || c == '\t') && pos == 0 && !feof( fp ) ) {
			c = fgetc( fp );
		}
		if( pos >= SCRIPT_MAX_STRING_LENGTH - 1 ) {
			//1行の文字数が多すぎる
			printf("error: 文字数が多すぎます (%d行目)", script->currentLine );
			return -1;
		}
		//改行文字が出てきた場合，次の行へ移動
		if( c == '\n' ) 
		{
			//空行は読み飛ばす
			if( pos == 0 ) 
			{
				continue;
			}
			
			//\0を文字列の最後に付ける
			script->script[ script->currentLine ][ pos ] = '\0';
			//次の行に移動
			script->currentLine++;
			//書き込み位置を0にする
			pos = 0;
		}
		else 
		{
			//書き込み
			script->script[ script->currentLine ][ pos ] = c;
			//文字書き込み位置をずらす
			pos++;
			
		}
		
	}
	//最大行数
	script->maxLineNumber = script->currentLine;
	//読み込み中の行を0にする
	script->currentLine = 0;
	//スクリプトファイル名を設定
	script->filename = filename;
	return 0;
}

//文字列分割(1行の最大文字数は SCRIPT_MAX_STRING_LENGTH)
//src : 分割したい文字列
//dest: 分割された文字列
//delim: 区切り文字
//splitNum : 最大分割数
void splitString(const char* src, char* dest[], const char* delim, int splitNum)
{
	int i;
	char* cp;
	char* copySrc;

	//元の文章をコピーする
	copySrc = (char*)malloc( sizeof(int) * SCRIPT_MAX_STRING_LENGTH + 1);
	strncpy( copySrc, src, SCRIPT_MAX_STRING_LENGTH );
	cp = copySrc;

	//strtokを使って copySrc をdelim区切りで分割する
	for( i = 0; i < splitNum ; i++ ) {
		//分割対象文字列が無くなるまで分割
		if( (dest[i] = strtok(cp, delim)) == NULL ) {
			break;
		}
		//2回目にstrtokを呼び出す時は，cpをNULLにする
		cp = NULL;
	}
	//分割された文字列の最後の要素はNULLとしておく
	dest[i] = NULL;
}

//スクリプト文を解読する
//戻り値 1: 成功  0: 失敗
int decodeScript(const char* scriptMessage, Script *self)
{
	//分割されたスクリプト文
	char* message[100];
	//条件分岐用
	char* selectMessage[10];
	char* select[10][2];

	//文字列分割時の区切り文字
	const char* delim = " ";
	const char* selectDelim = "@@";
	
	//スクリプト分割
	splitString( scriptMessage, message, delim, 100 );

	//分割に失敗した場合
	if( message[0] == NULL ) {
		return 0;
	}

	if(strncmp(message[0], "@@draw", SCRIPT_MAX_STRING_LENGTH) == 0)
	{
		//画像描画
		if(self->draw_order[atoi( message[1] )] == -1)
		{
			twod_add_image(self->twod, atoi( message[2] ), atoi( message[3] ), atoi( message[4] ),  message[5]);
			self->draw_order[atoi( message[1] )] = 0;
		}
		return 1;
	}
	else if(strncmp(message[0], "@@word", SCRIPT_MAX_STRING_LENGTH) == 0)
	{
		//文字描画
		if(self->word_order[atoi( message[1] )] == -1)
		{
			mess_add_word(self->mess,atoi( message[2] ), atoi( message[3] ), message[4] , message[5] );
			self->word_order[atoi( message[1] )] = 0;
		}
		return 1;
	}
	else if(strncmp(message[0], "@@reset", SCRIPT_MAX_STRING_LENGTH) == 0)
	{
		return -1;
	}
	else if( strncmp(message[0], "@@label", SCRIPT_MAX_STRING_LENGTH) == 0 ) 
	{
		//ラベルの場合はなにもしない
		printf("\ngyou = %d\n",self->currentLine);
		return 1;
	}

	return 1;
}

Words split(const char *str)
{
    istringstream ss(str);
    Words words;
    copy(I(ss), I(), std::back_inserter<Words>(words));
    return words;
}


int area_hougaku(Script *self, int area , int hougaku)
{
	if(self->area == area && self->hougaku == hougaku)
	{
		return 1;
	}

	return 0;
}

void word_act(Script *self, Words &words)
{
	if(words[0] == "check")
	{
		if(words.size() > 1)
		{
			if(words[1] == "door")
			{
				if(area_hougaku(self,0,0))
				{
					self->word_order[0] = -1;
				}
			}
			if(words[1] == "draw")
			{
				if(area_hougaku(self,1,3))
				{	
					self->draw_order[10] = -1;
					self->word_order[10] = -1;
				}
			}
		}
	}

	else if(words[0] == "open")
	{
		if(words.size() > 1)
		{
			if(words[1] == "door")
			{
				if(area_hougaku(self,0,0))
				{
					Room_set_open(self->room, 1);
				}
			}
		}
	}
	

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

void Script_set_area(Script *self, int area)
{
	self->area = area;
}

void Script_set_hougaku(Script *self, int hougaku)
{
	self->hougaku = hougaku;
}


// 動きを計算する
void Script_Update( Script *self )
{
	Camera_Update(self->camera);
	Room_Update( self->room );
	Console_Update( self->console );
	Mess_Update( self->mess );
	Twod_Update( self->twod );

	decode_command(self);

	int state_flag = decodeScript( self->script[ self->currentLine ], self );
	
	if(state_flag == 1)
	{
		//一般の命令後次の行へ
		self->currentLine++;
	}
	else if(state_flag == -1)
	{
		//@@resetの命令後0行目へ
		self->currentLine = 0;
	}

}	

// 描画する
void Script_Draw( Script *self)
{
	Camera_Draw(self->camera);
	Room_Draw(self->room);
	Console_Draw( self->console );
	Twod_Draw( self->twod );
	Mess_Draw(self->mess);
	
}

// 終了処理をする
void Script_Finalize( Script *self )
{
    
}
