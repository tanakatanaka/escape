#ifndef DEF_Player_H //“ñdinclude–h~

#define DEF_Player_H

struct Player;

// ‰Šú‰»‚ğ‚·‚é
Player *Player_Initialize();

// “®‚«‚ğŒvZ‚·‚é
void Player_Update( Player *Player );

// •`‰æ‚·‚é
void Player_Draw( Player *Player );

// I—¹ˆ—‚ğ‚·‚é
void Player_Finalize( Player *Player );

#endif