#ifndef DEF_Opening_H //“ñdinclude–h~

#define DEF_Opening_H

struct Opening;

// ‰Šú‰»‚ğ‚·‚é
Opening *Opening_Initialize();

//opening‚Ìó‘Ô‚ğ•Ô‚·
int Opening_get_game_mode(Opening *self);

// “®‚«‚ğŒvZ‚·‚é
void Opening_Update( Opening *Opening );

// •`‰æ‚·‚é
void Opening_Draw( Opening *Opening );

// I—¹ˆ—‚ğ‚·‚é
void Opening_Finalize( Opening *Opening );

#endif