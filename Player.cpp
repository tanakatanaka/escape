#include "DxLib.h"
#include "Pad.h"
#include "Player.h"

struct Player
{
    int area;
    int hougaku;
}; 

// ������������
Player *Player_Initialize( )
{
	Player *self;
	self = (Player *)malloc(sizeof(Player));
	return self;
}

// �������v�Z����
void Player_Update( Player *self )
{
    
}

// �`�悷��
void Player_Draw( Player *self)
{
    
}

// �I������������
void Player_Finalize( Player *self )
{
    
}
