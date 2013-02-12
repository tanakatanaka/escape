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
	self = (Mess *)malloc(sizeof(Mess));
	return self;
}

std::string alteration_word(std::string word)
{
	for(int i = 0; i < word.size(); i++)
	{
		if(word[i] == '_' && word[i + 1] == '_')
		{
			word.replace(i,i+1," ");
		}	
	}

	printf("\n %s \n", word.c_str());
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
	m.word = word;
	//m.word = alteration_word(word);
	m.tag = tag;
	self->mess.push_back(m);
	printf("\ndo do do\n");
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
	self->word.size();

}


// �������v�Z����
void Mess_Update( Mess *self )
{

}		

// �`�悷��
void Mess_Draw( Mess *self)
{
	if(self->mess.size() > 0)
	{
		for (int i = 0; i < self->mess.size(); i++)
		{
			if(self->mess[i].on_off != -1)
			{
				draw_words(&self->mess[i]);
			}
		}
	}
	
}

// �I������������
void Mess_Finalize( Mess *self )
{
    
}
