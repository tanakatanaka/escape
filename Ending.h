#ifndef DEF_ENDING_H //“ñdinclude–h~

#define DEF_ENDING_H

struct Ending;

#include "Player.h"

// ‰Šú‰»‚ğ‚·‚é
Ending *Ending_Initialize(Player *player);

int Ending_get_next( Ending *self );

// “®‚«‚ğŒvZ‚·‚é
void Ending_Update( Ending *Ending );

// •`‰æ‚·‚é
void Ending_Draw( Ending *Ending );

// I—¹ˆ—‚ğ‚·‚é
void Ending_Finalize( Ending *Ending );

#endif