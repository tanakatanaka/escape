#ifndef DEF_Player_H //��dinclude�h�~

#define DEF_Player_H

struct Player;

// ������������
Player *Player_Initialize();

//���ݒn�𓾂�
void Player_set_area(Player *self, int area);
//���p�𓾂�
void Player_set_hougaku(Player *self, int hougaku);

// �������v�Z����
void Player_Update( Player *Player );

// �`�悷��
void Player_Draw( Player *Player );

// �I������������
void Player_Finalize( Player *Player );

#endif