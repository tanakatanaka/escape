#include "string.h"
#include "DxLib.h"
#include "Mess.h"

//メッセージのフォントの大きさ
#define MESSAGE_FONT_SIZE 20
//仮想バッファの最大文字数
#define MESSAGE_MAX_LENGTH 10
//仮想バッファの最大行数
#define MESSAGE_MAX_LINE 5
//メッセージボックスのX座標
#define MESSAGE_BOX_X_POS 60
//メッセージボックスのY座標
#define MESSAGE_BOX_Y_POS 90

struct Word
{
   char g_message[MESSAGE_MAX_LENGTH * MESSAGE_MAX_LINE];
   int g_currentCursor; //現在の行で何文字目か
   int g_currentLineCursor;//現在何行目か
   int x; //メッセージボックスのx座標に加える数
   int y; //メッセージボックスのy座標に加える数
   int on_off;
   char tag[100];
};

struct Mess
{	
	Word word[100];
};

// 初期化をする
Mess *Mess_Initialize()
{
	Mess *self;
	self = (Mess *)malloc(sizeof(Mess));
	
	for(int i = 0; i < 100;i++)
	{
		self->word[i].on_off = -1;
	}
	/*
		strcpy(self->word[0].g_message,"はろーhelloわーるどWorldあいうえおかきくけこさしすせそたちつてとな");
		self->word[0].g_currentCursor = 0;
		self->word[0].g_currentLineCursor = 0;
		self->word[0].on_off = 1;
	*/
	return self;
}
void mess_add_word(Mess *self,int x, int y, const char *word, const char *tag)
{
	for(int i = 0; i < 100;i++)
	{
		if(self->word[i].on_off < 0)
		{
			self->word[i].on_off = 1;
			self->word[i].g_currentCursor = 0;
			self->word[i].g_currentLineCursor = 0;
			self->word[i].x = x;
			self->word[i].y = y;
			strcpy(self->word[i].g_message, word);
			strcpy(self->word[i].tag, tag);
			break;
		}
	}
}

void mess_erase_word(Mess *self, const char *tag)
{
	for (int i=0; i < 100; i++)
	{
		if (strcmp(self->word[i].tag, tag) == 0)
		{
			self->word[i].on_off = -1;
			break;
		}
	}
}


//code が日本語であるか判定する
//戻り値 1:日本語 0:日本語ではない
int isJapaneseCharacter(unsigned char code)
{
	if( (code >= 0x81 && code <= 0x9F) || 
		(code >= 0xE0 && code <= 0xFC) ) {
			return 1;
	}
	return 0;
}

//messageで指定した文章を start の位置から len 文字分表示する
void writeSubstring(char* message, int start, int len, int posX, int posY, int color, int bufferLine)
{
	int i;
	char g_messageBuffer[MESSAGE_MAX_LINE][MESSAGE_MAX_LENGTH];
	//文字数
	int maxLen = strlen( message );
	
	//startの位置を変更する
	//startの位置までに日本語がでてきていたら，1を足していく
	for( i = 0; i < start && message[i] != '\0'; ) {
		if( isJapaneseCharacter( message[i] ) ) {
			//日本語の場合，2バイト分すすめる
			i += 2;
			//startに1バイト分足す
			start++;
		}else {
			//半角文字の場合，1バイト分進める
			i++;
		}
	}

	//startの位置が表示したい最大文字数より大きい場合
	if( start >= maxLen ) {
		return;
	}

	//指定した位置からlen文字分表示する
	for( i = 0; i < len && message[ start + i ] != '\0'; ) {
		if( isJapaneseCharacter( message[ start + i ] ) ) {
			//日本語の場合，2文字分bufferにセット
			g_messageBuffer[ bufferLine ][ i ] = message[ start + i ];
			g_messageBuffer[ bufferLine ][ i + 1 ] = message[ start + i + 1 ];
			//lenは日本語なので，1バイト分追加する
			len++;
			//2バイト分進める
			i += 2;
		}else {
			//半角文字1文字をセット
			g_messageBuffer[ bufferLine ][ i ] = message[ start + i ];
			//1バイト分進める
			i++;
		}
	}
	g_messageBuffer[ bufferLine ][i] = '\0';

	//メッセージ描画
	DrawString(posX, posY, g_messageBuffer[ bufferLine ], color );
}

void drawMessage(Word *self)
{
	int i;
	int g_whiteColor = GetColor(255,255,255);//白
	int g_blackColor = GetColor(0, 0, 0);//黒

	if( self->g_message[self->g_currentCursor] != '\0' ) 
	{
		self->g_currentCursor++;
	}

	//MESSAGE_MAX_LENGTH まで文字を描画したら段落を切り替える
	if(self->g_currentCursor % MESSAGE_MAX_LENGTH == 0 ) {
		if( self->g_message[self->g_currentCursor] != '\0' ) {
			self->g_currentLineCursor++;
		}
	}

	//メッセージ描画部分
	for( i = 0; i < MESSAGE_MAX_LINE; i++ ) {
		if( i == self->g_currentLineCursor ) {
			//メッセージ風に表示
			writeSubstring( self->g_message, i * MESSAGE_MAX_LENGTH , self->g_currentCursor - MESSAGE_MAX_LENGTH * i,
				MESSAGE_BOX_X_POS + 15 + self->x, MESSAGE_BOX_Y_POS + MESSAGE_FONT_SIZE * i + 15 + self->y, g_whiteColor, i );
			break;
		}else {
			//メッセージをそのまま表示
			writeSubstring( self->g_message, i * MESSAGE_MAX_LENGTH , MESSAGE_MAX_LENGTH, MESSAGE_BOX_X_POS + 15 + self->x,
				MESSAGE_BOX_Y_POS + MESSAGE_FONT_SIZE * i + 15 + self->y, g_whiteColor, i );
		}
	}

}



// 動きを計算する
void Mess_Update( Mess *self )
{

}		

// 描画する
void Mess_Draw( Mess *self)
{
	for (int i=0; i < 100; i++)
	{
		if(self->word[i].on_off != -1)
		{
			drawMessage(&self->word[i]);
		}
	}

	
}

// 終了処理をする
void Mess_Finalize( Mess *self )
{
    
}
