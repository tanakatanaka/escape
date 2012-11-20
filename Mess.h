#ifndef DEF_Mess_H //“ñdinclude–h~

#define DEF_Mess_H

struct Mess;

// ‰Šú‰»‚ğ‚·‚é
Mess *Mess_Initialize();

// “®‚«‚ğŒvZ‚·‚é
void Mess_Update( Mess *Mess );

// •`‰æ‚·‚é
void Mess_Draw( Mess *Mess );

// I—¹ˆ—‚ğ‚·‚é
void Mess_Finalize( Mess *Mess );

#endif