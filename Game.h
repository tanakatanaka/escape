#ifndef DEF_Game_H //��dinclude�h�~

#define DEF_Game_H

struct Game;

// ������������
Game *Game_Initialize();

// �������v�Z����
void Game_Update(Game *game );

// �`�悷��
void Game_Draw(Game *game );

// �I������������
void Game_Finalize(Game *game );

#endif