#ifndef DEF_Script_H //“ñdinclude–h~

#define DEF_Script_H
#include "Camera.h"
#include "Console.h"

struct Script;

// ‰Šú‰»‚ğ‚·‚é
Script *Script_Initialize(Camera *self, Console *console);

// “®‚«‚ğŒvZ‚·‚é
void Script_Update( Script *Script );

// •`‰æ‚·‚é
void Script_Draw( Script *Script );

// I—¹ˆ—‚ğ‚·‚é
void Script_Finalize( Script *Script );

#endif