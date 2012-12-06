#include "DxLib.h"
#include <string.h>
#include <stdlib.h>
#include "Script.h"
#include "Room.h"
#include "Camera.h"
#include "Room.h"
#include "Mess.h"
#include "Twod.h"
#include "Pad.h"
#include "Console.h"


//スクリプトは最大1000行まで読み込む
#define SCRIPT_MAX_LINE 1000
//スクリプト最大文字数
#define SCRIPT_MAX_STRING_LENGTH 300

struct Script
{
	Room *room;
    Camera *camera;
    Mess *mess;
	Twod *twod;
	Console *console;
	int load_flag;
    int maxLineNumber;			//スクリプト行数
	int currentLine;			//現在何行目を実行しているか
	const char* filename;		//ファイル名
	char script[SCRIPT_MAX_LINE][SCRIPT_MAX_STRING_LENGTH];
};

int loadScript(const char* filename, Script *script);
int decodeScript(const char* scriptMessage, Script *script);
void splitString(const char* src, char* dest[], const char* delim, int splitNum);

// 初期化をする
Script *Script_Initialize( )
{
	Script *self;
	self = (Script *)calloc(sizeof(Script), 1);

	self->camera = Camera_Initialize( );
	self->room = Room_Initialize();
	self->mess = Mess_Initialize( );
	self->twod = Twod_Initialize( );
	self->console = Console_Initialize( );
	self->load_flag = 1;
	
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

//指定したラベルがある行数を探す
//戻り値 正の数: 指定したラベルの行番号 -1: エラー
int searchScriptLabel(const char* label, Script *script)
{
	//分割されたスクリプト文
	char* message[100];
	//文字列分割時の区切り文字
	const char* delim = " ";
	int i, line = -1;

	for( i = 0; i < script->maxLineNumber; i++ ) { 
		//スクリプト分割
		splitString( script->script[i] , message, delim, 100 );

		//分割に失敗した場合
		if( message[0] == NULL ) {
			return -1;
		}

		//指定したラベルを探す
		if( strncmp(message[0], "@@label", SCRIPT_MAX_STRING_LENGTH) == 0 ) {
			if( strncmp(message[1], label, SCRIPT_MAX_STRING_LENGTH) == 0 ) {
				//指定したラベルが見つかった時
				line = i;
				break;
			}
		}
	}

	return line;
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

//デバッグ用
//elemの要素を表示
void printElements(char* elem[])
{
	int i;
	for( i = 0; elem[i] != NULL; i++ ) {
		printf("%d : %s\n", i + 1, elem[i] );
	}
}

//スクリプト文を解読する
//戻り値 1: 成功  0: 失敗
int decodeScript(const char* scriptMessage, Script *self)
{
	int i, selectNum, choice, line;
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

	//scriptの仕様
	//
	//@@message 文字列
	//--- 文字列をメッセージとして表示する
	//@@select 条件1の場合@@LABEL1 条件2の場合@@LABEL2 条件3の場合@@LABEL3
	//--- 条件分岐
	
	//message[0] が @@message の時は，メッセージ命令が来たと判断
	if( strncmp(message[0], "@@message", SCRIPT_MAX_STRING_LENGTH) == 0 ) 
	{
		printf("メッセージ : %s\n", message[1] );
	}
	else if( strncmp(message[0], "@@drawgraph", SCRIPT_MAX_STRING_LENGTH) == 0 ) 
	{
		printf("画像 %s 表示 -- x座標 : %d, y座標 : %d\n", 
			message[3], atoi( message[1] ), atoi( message[2] ) );
	}
	else if(strncmp(message[0], "@@drawtest", SCRIPT_MAX_STRING_LENGTH) == 0 )
	{
		twod_add_image(self->twod, atoi( message[1] ), atoi( message[2] ), atoi( message[3] ),  message[4] );
	}
	else if(strncmp(message[0], "@@drawerase", SCRIPT_MAX_STRING_LENGTH) == 0 )
	{
		twod_erase_image(self->twod, message[1] );
	}

	else if( strncmp(message[0], "@@select", SCRIPT_MAX_STRING_LENGTH) == 0 ) {

		for(i = 0; message[i + 1] != NULL; i++ ) {
			//条件を条件文章とジャンプラベルとに分ける
			splitString( message[i + 1], selectMessage, selectDelim, 2 );
			//条件文章
			select[i][0] = selectMessage[0];
			//ラベル
			select[i][1] = selectMessage[1];
		}
		//分岐数
		selectNum = i;

		//ここで分岐を画面に表示
		for(i = 0; i < selectNum; i++) {
			printf("条件 %d : %s\n", i + 1, select[i][0] );
		}
		//分岐を選択
		choice = 0;
		while( choice <= 0 || choice > selectNum ) {
			printf("選択 :");
			scanf("%d", &choice );
		}

		//ラベルが何行目にあるかを取得
		line = searchScriptLabel( select[choice - 1][1] , self );
		//指定したラベルが見つからなかった
		if( line == -1 ) {
			printf("スクリプトエラー:条件分岐の指定ラベルが間違っています(%d行目)\n",
				self->currentLine + 1 );
			return 0;
		}
		//読み取り中の行番号をラベルの行に移動
		self->currentLine = line;

	}else if( strncmp(message[0], "@@goto", SCRIPT_MAX_STRING_LENGTH) == 0 ) {
		//ラベルが何行目にあるかを取得
		line = searchScriptLabel( message[1], self );
		//指定したラベルが見つからなかった
		if( line == -1 ) {
			printf("スクリプトエラー:指定したラベルが見つかりませんでした(%d行目)\n",
				self->currentLine + 1);
			return 0;
		}
		//読み取り中の行番号をラベルの行に移動
		self->currentLine = line;

	}else if( strncmp(message[0], "@@label", SCRIPT_MAX_STRING_LENGTH) == 0 ) {
		//ラベルの場合はなにもしない
	}
	

	return 1;
}

// 動きを計算する
void Script_Update( Script *self )
{
	Pad_Update(  );
	Camera_Update(self->camera);
	Room_Update( self->room );
	Console_Update( self->console );
	//Mess_Update( self->mess );
	Twod_Update( self->twod );
	

	if(self->load_flag == 1 && decodeScript( self->script[ self->currentLine ], self ) != 0)
	{
		self->currentLine++;
		self->load_flag = 0;	
	}

	if(Pad_Get(KEY_INPUT_Q) == 1 ){self->load_flag = 1;}

	//for( ; decodeScript( self->script[ self->currentLine ], self ) != 0 ; self->currentLine++ );
	

}

// 描画する
void Script_Draw( Script *self)
{
	Room_Draw(self->room);
	Console_Draw( self->console );
	Twod_Draw( self->twod );
	Mess_Draw(self->mess);
	
}

// 終了処理をする
void Script_Finalize( Script *self )
{
    
}
