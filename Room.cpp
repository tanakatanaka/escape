#include "DxLib.h"
#include "Room.h"


struct Room
{
    int room;
	double rotY;
}; 

// ������������
Room *Room_Initialize()
{
	Room *self;
	self = (Room *)malloc(sizeof(Room));
    self->room = MV1LoadModel("meta/room.mqo") ;    //�摜�n���h���̊i�[
	self->rotY = 0.0f;
	return self;
}

// �������v�Z����
void Room_Update( Room *self )
{
	MV1SetPosition(self->room, VGet( 200.0f, 0.0f, 300.0f ) );
    MV1SetRotationXYZ( self->room, VGet( 0.0f, self->rotY, 0.0f ) );

	/*if(CheckHitKey(KEY_INPUT_A)){self->rotY -= (PHI / 180.0f);}
	  else if(CheckHitKey(KEY_INPUT_D)){self->rotY += (PHI / 180.0f);}
    */
}		

// �`�悷��
void Room_Draw( Room *self)
{
	for(int i = 0;  i < MV1GetFrameNum(self->room);i++)
	{
		MV1DrawFrame( self->room,i);
	}    
}

// �I������������
void Room_Finalize( Room *self )
{
    
}
