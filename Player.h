#ifndef DEF_PLAYER_H //��dinclude�h�~

#define DEF_PLAYER_H

typedef struct{
    int Image;
    int y;
} Player_t;

// ������������
void Player_Initialize( Player_t *Player, int y, int img );

// �������v�Z����
void Player_Update( Player_t *Player );

// �`�悷��
void Player_Draw( Player_t Player );

// �I������������
void Player_Finalize( Player_t Player );

#endif