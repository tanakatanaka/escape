#include "DxLib.h"
#include <deque>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <fstream>
#include "Pad.h"
#include "Compiler.h"

typedef std::vector<std::string> Words;

struct Compiler
{
	//命令構造体変数 
	std::vector<When> when;
	std::vector<Condition> condition;
	std::vector<Condition> notice;
	std::vector<Effect> effect;
};

void pack_when_words(Compiler *self, Words &line)
{
	When w;

	w.condition_name = line[3];
	w.state_name = line[1];
	w.state = std::stoi(line[2]);

}

void pack_conditon_words(Compiler *self, Words &line)
{
	Condition c;

	c.effect_name = line[1].c_str();
	c.area = std::stoi(line[2]);
	c.hougaku = std::stoi(line[3]);
	
	if(line[0] == "con")
	{
		c.order = line[4].c_str();
		c.object = line[5].c_str();

		if(line.size() > 6){ c.special = line[6]; }
		else{ c.special = "non"; }

		self->condition.push_back(c);
	}
	else if(line[0] == "not")
	{
		c.one_time = true;
		self->notice.push_back(c);
	}

	
}

void pack_effect_words(Compiler *self, Words &line)
{
	Effect e;
			
	e.name = line[1].c_str();

	if(line[2] == "draw")
	{
		e.effect_type = "draw";
		e.draw_id = std::stoi(line[3]);
	}
	else if(line[2] == "text")
	{
		e.effect_type = "text";
		e.text = line[3].c_str();
	}
	else if(line[2] == "act")
	{
		e.effect_type = "act";
		// eff と act は飛ばして記録
		e.action = Words(line.begin() + 2, line.end());
	}

	if(line[2] == "draw" || line[2] == "text")
	{
		e.x = std::stoi(line[4]);
		e.y = std::stoi(line[5]);
	}
	self->effect.push_back(e);
}

Words split(const std::string &str)
{
    typedef std::istream_iterator<std::string> I;
    std::istringstream ss(str);
    Words words;
    std::copy(I(ss), I(), std::back_inserter<Words>(words));
    return words;
}


int load_script(Compiler *self, const char *filename)
{
	std::string line; //1行読み込み用
	std::ifstream file(filename); // ファイルを読み込み

	if (file.fail())
	{
		//ファイル読み込みに失敗
		printf("スクリプト %s を読み込めませんでした\n", filename);
		return -1;
	}

	while (std::getline(file, line))
	{
		Words word_line = split(line);
		
		if(word_line.size() > 0)
		{
			// １行をブロックにして構造体に代入
			if(word_line[0] == "when"){ pack_when_words(self, word_line); }
			else if(word_line[0] == "con" || word_line[0] == "not"){ pack_conditon_words(self, word_line); }
			else if(word_line[0] == "eff"){ pack_effect_words(self, word_line); }
		}
	}
	return 0;
}

CompilerResult Compiler_compile(Compiler *self, const char *filename)
{
	printf("\nスクリプト読み込み　開始\n\n");

	if(load_script(self, filename) == -1)
	{
		MessageBox(NULL,"ファイルが読み込みませんでした","ゲームのエラー", 0);
	}

	CompilerResult com;

	com.when = self->when;
	com.condition = self->condition;
	com.notice = self->notice;
	com.effect = self->effect;

	return com;
}

// 初期化をする
Compiler *Compiler_Initialize( )
{
	Compiler *self;
	self = new Compiler();


	return self;
}


// 終了処理をする
void Compiler_Finalize( Compiler *self )
{
	
}
