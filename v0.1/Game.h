#ifndef DEF_Game_H //��dinclude�h�~

#define DEF_Game_H

struct Game_t;

// ������������
Game_t Game_Initialize();

// �������v�Z����
void Game_Update( Game_t *Game );

// �`�悷��
void Game_Draw( Game_t *Game );

// �I������������
void Game_Finalize( Game_t *Game );

#endif