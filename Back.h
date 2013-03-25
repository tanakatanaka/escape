#ifndef DEF_Back_H //“ñdinclude–h~

#define DEF_Back_H

struct Back;

#include "Camera.h"

// ‰Šú‰»‚ğ‚·‚é
Back *Back_Initialize(Camera *camera);

// “®‚«‚ğŒvZ‚·‚é
void Back_Update( Back *Back );

// •`‰æ‚·‚é
void Back_Draw( Back *Back );

// I—¹ˆ—‚ğ‚·‚é
void Back_Finalize( Back *Back );

#endif