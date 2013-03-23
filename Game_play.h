#ifndef DEF_Game_play_H //“ñdinclude–h~

#define DEF_Game_play_H

struct Game_play;

#include "Player.h"

// ‰Šú‰»‚ğ‚·‚é
Game_play *Game_play_Initialize();

//Game_playI—¹ğŒ‚ğ“¾‚é
Player *Game_play_get_result(Game_play *game_play);

// “®‚«‚ğŒvZ‚·‚é
void Game_play_Update(Game_play *game_play );

// •`‰æ‚·‚é
void Game_play_Draw(Game_play *game_play );

// I—¹ˆ—‚ğ‚·‚é
void Game_play_Finalize(Game_play *game_play );

#endif