#include "DxLib.h"
#include "Keyboard.h"
#include "Player.h"

struct Player
{
    int Image;
    int y;
}; 

// ������������
Player *Player_Initialize( int y, int img )
{
	Player *self;
	self = (Player *)malloc(sizeof(Player));
    self->Image = img;    //�摜�n���h���̊i�[
    self->y     = y;        //y���W�i�[
	return self;
}

// �������v�Z����
void Player_Update( Player *self )
{
    if( Keyboard_Get( KEY_INPUT_UP   ) > 0 )
	{//�オ������Ă�����
        self->y--;
    }
    if( Keyboard_Get( KEY_INPUT_DOWN ) > 0 )
	{//����������Ă�����
        self->y++;
    }
}

// �`�悷��
void Player_Draw( Player *self){
    DrawGraph( 0, self->y, self->Image, TRUE );
}

// �I������������
void Player_Finalize( Player *self )
{
    DeleteGraph( self->Image );
}
