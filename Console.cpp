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

int Console_over(Console *self)
{
	return self->win_s % 2;
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

	//�G���^�[���͂��������ꍇ
	if(Pad_Get( KEY_INPUT_RETURN ) == -1){return -3;}

	//�X�y�[�X���͂��������ꍇ
	if(Pad_Get( KEY_INPUT_SPACE ) == -1){return ' ';}



  //���͂��Ȃ������ꍇ
  return -1;
}

void split_string(char *code)
{
	char *tp;
	char *box[10];
	printf("\ncode = %s\n",code);

	for(int i = 0; i < 2 ; i++ )
	{
		//�����Ώە����񂪖����Ȃ�܂ŕ���
		if( (box[i] = strtok(code, " ")) == NULL )
		{
			break;
		}

		printf("\narea = %s\n",box[i]);
		//2��ڂ�strtok���Ăяo�����́Ccp��NULL�ɂ���
		code = NULL;
	}
        
		
		
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
		else if(bag == -3)
		{
			//�G���^�[���͂��������ꍇ
			self->log.push_back(self->d_bag);
			char code[100];
			strcpy( code,self->d_bag.c_str() );
			split_string(code);
			self->d_bag.erase(0);

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
	
	
	DrawFormatString( self->x, 465 - 15, self->moji_c, "%s", self->log); // log��`�悷��
	DrawFormatString( self->x, 465, self->moji_c, "%s", self->d_bag.c_str()); // ���݂̕�����`�悷��
}

// �I������������
void Console_Finalize( Console *self )
{
	
}
