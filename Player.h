#ifndef DEF_PLAYER_H //��dinclude�h�~

#define DEF_PLAYER_H

struct Player_t;

// ������������
Player_t Player_Initialize( int y, int img );

// �������v�Z����
void Player_Update( Player_t *Player );

// �`�悷��
void Player_Draw( Player_t *Player );

// �I������������
void Player_Finalize( Player_t *Player );

#endif