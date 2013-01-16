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

static const int KEYNUM[] =
{
	D_DIK_0, D_DIK_1, D_DIK_2, D_DIK_3, D_DIK_4, 
	D_DIK_5, D_DIK_6, D_DIK_7, D_DIK_8, D_DIK_9
};


struct Console
{
	int mode;
	int x;
	int y;
	int ly;
	int back_count;
	std::string d_bag;
	std::deque<std::string> log;
}; 

// ������������
Console *Console_Initialize()
{
	Console *self;
	self =  new Console();
	self->mode = 0;
	self->x = 0;
	self->y = 420;
	self->back_count = 0;
	return self;
}

void Console_get_mode(Console *self, int mode)
{
	self->mode = mode;
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
	    if (Pad_Get( KEYCODES[i] ) == -1){return  'a'+ i;}
	}

	//���l���͂��������ꍇ
	for (int i = 0; i < 10; i++)
	{
		if (Pad_Get( KEYNUM[i] ) == -1){return  '0'+ i;}
	}

	//�X�y�[�X���͂��������ꍇ
	if(Pad_Get( KEY_INPUT_SPACE ) == -1){return ' ';}
	//�o�b�N�X�y�[�X���͂��������ꍇ
	if(Pad_Get( KEY_INPUT_BACK ) == -1){return -2;}
	//��L�[���͂��������ꍇ
	if(Pad_Get( KEY_INPUT_UP ) == -1){return -3;}
	//�����L�[���͂��������ꍇ
	if(Pad_Get( KEY_INPUT_DOWN ) == -1){return -4;}

  //���͂��Ȃ������ꍇ
  return -1;
}

// �������v�Z����
void Console_Update( Console *self )
{
	//���̓��[�h��
	if(self->mode % 2 == 1)
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
			if(!self->d_bag.empty()){self->d_bag.erase(self->d_bag.size() - 1);}

		}
		else if(bag == -3)
		{
			//��L�[���͂��������ꍇ
			int in = self->log.size()- 1 - self->back_count;
			if(self->log.size() > self->back_count)
			{
				self->d_bag.erase(0); 
				self->d_bag.append(self->log[in]);
				if(in > 0){self->back_count++;}
			}
			
		}
		else if(bag == -4)
		{
			//���L�[���͂��������ꍇ
			int in = self->log.size()- 1 - self->back_count;
			if(in > -1)
			{
				self->d_bag.erase(0); 
				self->d_bag.append(self->log[in]);
				if(self->back_count > 0){self->back_count--;}
			}
			
		}
		else
		{
			//�����E���l���͂��������ꍇ�ǉ�
			self->d_bag += (char) bag;
		}
	}
	//���̓��[�h�ȊO
	else{self->back_count = 0;}

}

// �`�悷��
void Console_Draw( Console *self)
{
	SetDrawBlendMode( DX_BLENDMODE_ALPHA, 128 ) ;
	
	int plus;
	if(self->mode % 2 == 1){plus = -40;}
	else{plus = 0;}

	DrawBox( 0, 420 +  plus, 640 , 480, GetColor( 0 , 0 , 200 ), TRUE) ;
	
	if(self->mode % 2 == 1)
	{
		for (int i = 0; i < self->log.size() ; i++)
		{
			DrawFormatString( self->x, 435 - i * 15, GetColor( 255, 255, 0 ), "%s", self->log[self->log.size()-1 - i].c_str()); //���O��`�悷��
			if(i == 3){break;}
		}
		DrawFormatString( self->x, 465, GetColor( 0, 255, 0 ), "%s", self->d_bag.c_str()); // ���݂̕�����`�悷��


	}

	
}

// �I������������
void Console_Finalize( Console *self )
{
	
}
