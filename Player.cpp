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
	
	self->area = 0;
	self->hougaku = 0;
	return self;
}

void Player_set_area(Player *self, int area)
{
	self->area = area;
}

void Player_set_hougaku(Player *self, int hougaku)
{
	self->hougaku = hougaku;
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
