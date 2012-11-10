#ifndef DEF_Game_H //“ñdinclude–h~

#define DEF_Game_H

typedef struct{
    
} Game_t;

// ‰Šú‰»‚ğ‚·‚é
void Game_Initialize( Game_t *Game);

// “®‚«‚ğŒvZ‚·‚é
void Game_Update( Game_t *Game );

// •`‰æ‚·‚é
void Game_Draw( Game_t Game );

// I—¹ˆ—‚ğ‚·‚é
void Game_Finalize( Game_t Game );

#endif