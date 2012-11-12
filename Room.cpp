#include "DxLib.h"
#include "Keyboard.h"
#include "Room.h"

struct Room
{
    int model;
}; 

// ������������
Room *Room_Initialize()
{
	Room *self;
	self = (Room *)malloc(sizeof(Room));
    self->model = MV1LoadModel("room.mqo") ;    //�摜�n���h���̊i�[
	MV1SetPosition(self->model, VGet( 320.0f, -300.0f, 600.0f ) ) ;
	return self;
}

// �������v�Z����
void Room_Update( Room *self )
{
    if( Keyboard_Get( KEY_INPUT_UP   ) > 0 )
	{//�オ������Ă�����
       
    }
    if( Keyboard_Get( KEY_INPUT_DOWN ) > 0 )
	{//����������Ă�����
        
    }
}

// �`�悷��
void Room_Draw( Room *self)
{
	MV1DrawModel( self->model);    
}

// �I������������
void Room_Finalize( Room *self )
{
    
}
