#ifndef DEF_Twod_H //“ñdinclude–h~

#define DEF_Twod_H

struct Twod;

#include "Player.h"

// ‰Šú‰»‚ğ‚·‚é
Twod *Twod_Initialize(Player *player);
//‰æ‘œ‚ğ•`‰æƒ‚[ƒh‚É‚·‚é
void Twod_add_image(Twod *self, int x, int y, int id);
//‰æ‘œ‚ğÁ‚·
void Twod_erase_image(Twod *self);
// “®‚«‚ğŒvZ‚·‚é
void Twod_Update( Twod *Twod );
// •`‰æ‚·‚é
void Twod_Draw( Twod *Twod );
// I—¹ˆ—‚ğ‚·‚é
void Twod_Finalize( Twod *Twod );

#endif