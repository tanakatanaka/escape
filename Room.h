#ifndef DEF_Room_H //“ñdinclude–h~

#define DEF_Room_H

struct Room;

#include "Player.h"

// ‰Šú‰»‚ğ‚·‚é
Room *Room_Initialize(Player *player);

void Room_set_door(Room *self);

// “®‚«‚ğŒvZ‚·‚é
void Room_Update( Room *Room );

// •`‰æ‚·‚é
void Room_Draw( Room *Room );

// I—¹ˆ—‚ğ‚·‚é
void Room_Finalize( Room *Room );

#endif