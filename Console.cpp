#include "DxLib.h"
#include <string>
#include <deque>
#include "Console.h"
#include "Pad.h"

static const int KEYCODES[] =
{
	D_DIK_A, D_DIK_B, D_DIK_C, D_DIK_D, D_DIK_E,
	D_DIK_F, D_DIK_G, D_DIK_H, D_DIK_I, D_DIK_J,
	D_DIK_K, D_DIK_L, D_DIK_M, D_DIK_N, D_DIK_O,
	D_DIK_P, D_DIK_Q, D_DIK_R, D_DIK_S, D_DIK_T,
	D_DIK_U, D_DIK_V, D_DIK_W, D_DIK_X, D_DIK_Y,
	D_DIK_Z
};


struct Console
{
	int win_s;
	int win_c;
	int moji_c;
	int x;
	int y;
	int ly;
	std::string d_bag;
	std::deque<std::string> log;
}; 

// ������������
Console *Console_Initialize()
{
	Console *self;
	self =  new Console();
	self->win_s = 0;
	self->win_c = GetColor( 0 , 0 , 200 );
	self->moji_c = GetColor( 0, 255, 0 );
	self->x = 0;
	self->y = 420;
	return self;
}

int console_state(Console *self)
{
	return self->win_s % 2;
}

const char *console_d_bag(Console *self)
{
	if( self->d_bag.empty()){return NULL;}
	else{return self->d_bag.c_str();}
}

void console_shift_log(Console *self)
{
	self->log.push_back(self->d_bag);
	self->d_bag.erase(0);
}

static int get_chara()
{
	for (int i = 0; i < 26; i++)
  	{
	    if (Pad_Get( KEYCODES[i] ) == -1)
	    {
			return  'a'+ i;
	    }
	}
	//�o�b�N�X�y�[�X���͂��������ꍇ
	if(Pad_Get( KEY_INPUT_BACK ) == -1){return -2;}
	//�X�y�[�X���͂��������ꍇ
	if(Pad_Get( KEY_INPUT_SPACE ) == -1){return ' ';}



  //���͂��Ȃ������ꍇ
  return -1;
}

// �������v�Z����
void Console_Update( Console *self )
{
	
	if(Pad_Get(KEY_INPUT_ESCAPE) == 1 ){self->win_s++;}


	if(self->win_s % 2 == 1)
	{
		int bag = get_chara();

		if(bag == -1)
		{
			//���͂��Ȃ��ꍇ
		}
		else if(bag == -2)
		{
			//�o�b�N�X�y�[�X���͂��������ꍇ
			//�Ō�̕���������
			self->d_bag.erase(self->d_bag.size() - 1);

		}
		else
		{
			//�������͂��������ꍇ�ǉ�
			self->d_bag += (char) bag;
		}
		
	}
	else
	{
		//�R���\�[���Ƃ�	
	}

}

// �`�悷��
void Console_Draw( Console *self)
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 ) ;
	
	int plus;
	if(self->win_s % 2 == 1){plus = -40;}
	else{plus = 0;}

	DrawBox( 0, 420 +  plus, 640 , 480, self->win_c, TRUE) ;
	

	for (int i = 0; i < self->log.size(); i++)
	{
		DrawFormatString( self->x, 435 - i * 15, self->moji_c, "%s", self->log[i].c_str()); //���O��`�悷��
	}
	
	DrawFormatString( self->x, 465, self->moji_c, "%s", self->d_bag.c_str()); // ���݂̕�����`�悷��
}

// �I������������
void Console_Finalize( Console *self )
{
	
}
