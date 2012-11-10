#ifndef DEF_PLAYER_H //“ñdinclude–h~

#define DEF_PLAYER_H

typedef struct{
    int Image;
    int y;
} Player_t;

// ‰Šú‰»‚ğ‚·‚é
void Player_Initialize( Player_t *Player, int y, int img );

// “®‚«‚ğŒvZ‚·‚é
void Player_Update( Player_t *Player );

// •`‰æ‚·‚é
void Player_Draw( Player_t Player );

// I—¹ˆ—‚ğ‚·‚é
void Player_Finalize( Player_t Player );

#endif