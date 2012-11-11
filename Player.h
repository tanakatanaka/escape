#ifndef DEF_PLAYER_H //“ñdinclude–h~

#define DEF_PLAYER_H

struct Player_t;

// ‰Šú‰»‚ğ‚·‚é
Player_t Player_Initialize( int y, int img );

// “®‚«‚ğŒvZ‚·‚é
void Player_Update( Player_t *Player );

// •`‰æ‚·‚é
void Player_Draw( Player_t *Player );

// I—¹ˆ—‚ğ‚·‚é
void Player_Finalize( Player_t *Player );

#endif