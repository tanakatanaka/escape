#ifndef DEF_COMPILER_H //二重include防止

#define DEF_COMPILER_H

struct Compiler;

struct Condition
{
	//命令条件の構造体
	//管理番号・場所・方角・命令内容・命令対象
	std::string effect_name;
	int area;
	int hougaku;
	std::string order;
	std::string object;
	std::string special;
	bool one_time;
	
};

struct Effect
{
	//命令効果の構造体
	//管理番号・y・効果番号(0:画像表示・1:文字表示)・画像管理番号・画像の名前・文字・画像文字の管理タグ
	std::string name;
	int x;
	int y;
	std::string effect_type;
	int draw_id; //描画関連
	std::string text;//文字関連
	Words action;//act関連
};

struct CompilerResult
{
    std::vector<Condition> condition;
	std::vector<Condition> notice;
	std::vector<Effect> effect;
};

CompilerResult Compiler_compile(Compiler *self, const char *filename);

// 初期化をする
Compiler *Compiler_Initialize();

// 終了処理をする
void Compiler_Finalize( Compiler *Compiler );

#endif