#ifndef DEF_Back_H //“ñdinclude–h~

#define DEF_Back_H

struct Back;


// ‰Šú‰»‚ğ‚·‚é
Back *Back_Initialize();

// “®‚«‚ğŒvZ‚·‚é
void Back_Update( Back *Back );

// •`‰æ‚·‚é
void Back_Draw( Back *Back );

// I—¹ˆ—‚ğ‚·‚é
void Back_Finalize( Back *Back );

#endif