#include "string.h"
#include "DxLib.h"
#include "Mess.h"
#include <string>
#include <vector>
#include "Pad.h"

struct Word
{
   std::string word;
   int cursor; //���݂̍s�ŉ������ڂ�
   int line_cursor;//���݉��s�ڂ�
   int x; //���b�Z�[�W�{�b�N�X��x���W�ɉ����鐔
   int y; //���b�Z�[�W�{�b�N�X��y���W�ɉ����鐔
   int on_off;
};

struct Mess
{	
	std::vector<Word> mess;
};

// ������������
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


// �������v�Z����
void Mess_Update( Mess *self )
{
	if(Pad_Get( KEY_INPUT_DELETE ) == -1)
	{
		Mess_erase_word(self);
	}

}		

// �`�悷��
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

// �I������������
void Mess_Finalize( Mess *self )
{
    delete self;
}
