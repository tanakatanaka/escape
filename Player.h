#ifndef DEF_PLAYER_H //“ñdinclude–h~

#define DEF_PLAYER_H

struct Player;

// ‰Šú‰»‚ğ‚·‚é
Player Player_Initialize( int y, int img );

// “®‚«‚ğŒvZ‚·‚é
void Player_Update( Player *Player );

// •`‰æ‚·‚é
void Player_Draw( Player *Player );

// I—¹ˆ—‚ğ‚·‚é
void Player_Finalize( Player *Player );

#endif