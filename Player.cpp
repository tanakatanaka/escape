#include "DxLib.h"
#include "Keyboard.h"
#include "Player.h"

struct Player
{
    int Image;
    int y;
} 

// ������������
Player Player_Initialize( int y, int img )
{
	Player *self;
	self = (Player *)malloc(sizeof(Player));
    Player->Image = img;    //�摜�n���h���̊i�[
    Player->y     = y;        //y���W�i�[
	return *self;
}

// �������v�Z����
void Player_Update( Player *Player )
{
    if( Keyboard_Get( KEY_INPUT_UP   ) > 0 )
	{//�オ������Ă�����
        Player->y--;
    }
    if( Keyboard_Get( KEY_INPUT_DOWN ) > 0 )
	{//����������Ă�����
        Player->y++;
    }
}

// �`�悷��
void Player_Draw( Player Player ){
    DrawGraph( 0, Player.y, Player.Image, TRUE );
}

// �I������������
void Player_Finalize( Player Player )
{
    DeleteGraph( Player.Image );
}
