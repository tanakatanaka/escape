#include "string.h"
#include "DxLib.h"
#include "Mess.h"
#include <string>
#include <vector>

struct Word
{
   std::string word;
   int cursor; //���݂̍s�ŉ������ڂ�
   int line_cursor;//���݉��s�ڂ�
   int x; //���b�Z�[�W�{�b�N�X��x���W�ɉ����鐔
   int y; //���b�Z�[�W�{�b�N�X��y���W�ɉ����鐔
   int on_off;
   std::string tag;
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


// �������v�Z����
void Mess_Update( Mess *self )
{

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
    
}
