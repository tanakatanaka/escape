#ifndef DEF_COMPILER_H //��dinclude�h�~

#define DEF_COMPILER_H

struct Compiler;

struct Condition
{
	//���ߏ����̍\����
	//�Ǘ��ԍ��E�ꏊ�E���p�E���ߓ��e�E���ߑΏ�
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
	//���ߌ��ʂ̍\����
	//�Ǘ��ԍ��Ey�E���ʔԍ�(0:�摜�\���E1:�����\��)�E�摜�Ǘ��ԍ��E�摜�̖��O�E�����E�摜�����̊Ǘ��^�O
	std::string name;
	int x;
	int y;
	std::string effect_type;
	int draw_id; //�`��֘A
	std::string text;//�����֘A
	Words action;//act�֘A
};

struct CompilerResult
{
    std::vector<Condition> condition;
	std::vector<Condition> notice;
	std::vector<Effect> effect;
};

CompilerResult Compiler_compile(Compiler *self, const char *filename);

// ������������
Compiler *Compiler_Initialize();

// �I������������
void Compiler_Finalize( Compiler *Compiler );

#endif