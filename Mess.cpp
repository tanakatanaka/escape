#include "string.h"
#include "DxLib.h"
#include "Mess.h"
#include <string>
#include <vector>

struct Word
{
   std::string word;
   int cursor; //現在の行で何文字目か
   int line_cursor;//現在何行目か
   int x; //メッセージボックスのx座標に加える数
   int y; //メッセージボックスのy座標に加える数
   int on_off;
   std::string tag;
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

std::string alteration_word(std::string word)
{
	for(int i = 0; i < word.size(); i++)
	{
		if(word[i] == '_' && word[i + 1] == '_')
		{
			word.replace(i, 2, " ");
		}	
	}

	return word;
}

void Mess_add_word(Mess *self,int x, int y, const char *word, const char *tag)
{
	Word m;

	m.on_off = 1;
	m.cursor = 0;
	m.line_cursor = 0;
	m.x = x;
	m.y = y;
	m.word = alteration_word(word);
	m.tag = tag;
	self->mess.push_back(m);
}

void mess_erase_word(Mess *self, const char *tag)
{
	for (int i = 0; i < self->mess.size(); i++)
	{
		if (self->mess[i].tag == tag)
		{
			self->mess[i].on_off = -1;
			break;
		}
	}
}



void draw_words(Word *self)
{
	int white = GetColor(255,255,255);
	std::string now_word = self->word.substr( 0, self->line_cursor);

	DrawFormatString( self->x, self->y, white, "%s", now_word.c_str()); 

	self->line_cursor++;
}


// 動きを計算する
void Mess_Update( Mess *self )
{

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
    
}
