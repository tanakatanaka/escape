#ifndef DEF_PLAYER_H //��dinclude�h�~

#define DEF_PLAYER_H

struct Player;

// ������������
Player Player_Initialize( int y, int img );

// �������v�Z����
void Player_Update( Player *Player );

// �`�悷��
void Player_Draw( Player *Player );

// �I������������
void Player_Finalize( Player *Player );

#endif