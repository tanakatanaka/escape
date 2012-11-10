#include "DxLib.h"
#include "Keyboard.h"
#include "Player.h"

// ������������
void Player_Initialize( Player_t *Player, int y, int img ){
    Player->Image = img;    //�摜�n���h���̊i�[
    Player->y     = y;        //y���W�i�[
}

// �������v�Z����
void Player_Update( Player_t *Player ){
    if( Keyboard_Get( KEY_INPUT_UP   ) > 0 ){//�オ������Ă�����
        Player->y--;
    }
    if( Keyboard_Get( KEY_INPUT_DOWN ) > 0 ){//����������Ă�����
        Player->y++;
    }
}

// �`�悷��
void Player_Draw( Player_t Player ){
    DrawGraph( 0, Player.y, Player.Image, TRUE );
}

// �I������������
void Player_Finalize( Player_t Player ){
    DeleteGraph( Player.Image );
}
