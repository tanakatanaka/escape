#ifndef DEF_Twod_H //“ñdinclude–h~

#define DEF_Twod_H

struct Twod;

// ‰Šú‰»‚ğ‚·‚é
Twod *Twod_Initialize();
//test
void Get_twod(Twod *self, int i);
// “®‚«‚ğŒvZ‚·‚é
void Twod_Update( Twod *Twod );
// •`‰æ‚·‚é
void Twod_Draw( Twod *Twod );
// I—¹ˆ—‚ğ‚·‚é
void Twod_Finalize( Twod *Twod );

#endif