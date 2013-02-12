#ifndef DEF_Script_H //“ñdinclude–h~

#define DEF_Script_H
#include "Camera.h"
#include "Console.h"
#include "Player.h"
#include "Script.h"
#include "Room.h"

struct Script;

// ‰Šú‰»‚ğ‚·‚é
Script *Script_Initialize(Camera *camera, Console *console, Player *player, Room *room);

// “®‚«‚ğŒvZ‚·‚é
void Script_Update( Script *Script );

// •`‰æ‚·‚é
void Script_Draw( Script *Script );

// I—¹ˆ—‚ğ‚·‚é
void Script_Finalize( Script *Script );

#endif