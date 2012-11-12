#ifndef DEF_Game_H //“ñdinclude–h~

#define DEF_Game_H

struct Game;

// ‰Šú‰»‚ğ‚·‚é
Game *Game_Initialize();

// “®‚«‚ğŒvZ‚·‚é
void Game_Update(Game *game );

// •`‰æ‚·‚é
void Game_Draw(Game *game );

// I—¹ˆ—‚ğ‚·‚é
void Game_Finalize(Game *game );

#endif