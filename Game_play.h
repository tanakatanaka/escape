#ifndef DEF_Game_play_H //��dinclude�h�~

#define DEF_Game_play_H

struct Game_play;

#include "Player.h"

// ������������
Game_play *Game_play_Initialize();

//Game_play�I�������𓾂�
Player *Game_play_get_result(Game_play *game_play);

// �������v�Z����
void Game_play_Update(Game_play *game_play );

// �`�悷��
void Game_play_Draw(Game_play *game_play );

// �I������������
void Game_play_Finalize(Game_play *game_play );

#endif