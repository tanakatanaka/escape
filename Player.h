#ifndef DEF_Player_H //“ñdinclude–h~

#define DEF_Player_H

struct Player;

#include "Camera.h"
#include "Console.h"

// ‰Šú‰»‚ğ‚·‚é
Player *Player_Initialize(Camera *camera, Console *console);

//Œ»İ’n‚ğ“¾‚é
void Player_set_area(Player *self, int area);
//•ûŠp‚ğ“¾‚é
void Player_set_hougaku(Player *self, int hougaku);

// “®‚«‚ğŒvZ‚·‚é
void Player_Update( Player *Player );

// •`‰æ‚·‚é
void Player_Draw( Player *Player );

// I—¹ˆ—‚ğ‚·‚é
void Player_Finalize( Player *Player );

#endif