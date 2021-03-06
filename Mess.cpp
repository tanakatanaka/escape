#include "string.h"
#include "DxLib.h"
#include "Mess.h"
#include <string>
#include <vector>
#include "Pad.h"

struct Word
{
   std::string word;
   int cursor; //現在の行で何文字目か
   int line_cursor;//現在何行目か
   int x; //メッセージボックスのx座標に加える数
   int y; //メッセージボックスのy座標に加える数
   int on_off;
};

struct Mess
{	
	std::vector<Word> mess;
};

// 初期化をする
Mess *Mess_Initialize()
{
	Mess *self;
	self = new Mess();
	return self;
}

void Mess_add_word(Mess *self,int x, int y, const char *word)
{
	Word m;

	m.on_off = 1;
	m.cursor = 0;
	m.line_cursor = 0;
	m.x = x;
	m.y = y;
	m.word = word;
	self->mess.push_back(m);
}

void Mess_erase_word(Mess *self)
{
	for (int i = 0; i < self->mess.size(); i++)
	{
		self->mess[i].on_off = -1;	
	}
}



void draw_words(Word *self)
{
	int white = GetColor(255,255,255);
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180) ;
	SetFontSize(16) ;

	DrawBox( self->x, self->y, self->x + self->line_cursor * 10, self->y + 15, GetColor( 0 , 200 , 0 ), TRUE) ;

	std::string now_word = self->word.substr( 0, self->line_cursor);
	DrawFormatString( self->x, self->y, white, "%s", now_word.c_str()); 
	
	if(self->word.size() > self->line_cursor){ self->line_cursor++; }
}


// 動きを計算する
void Mess_Update( Mess *self )
{
	if(Pad_Get( KEY_INPUT_DELETE ) == -1)
	{
		Mess_erase_word(self);
	}

}		

// 描画する
void Mess_Draw( Mess *self)
{
	for (int i = 0; i < self->mess.size(); i++)
	{
		if(self->mess[i].on_off != -1)
		{
			draw_words(&self->mess[i]);
		}
	}
}	

// 終了処理をする
void Mess_Finalize( Mess *self )
{
    delete self;
}
